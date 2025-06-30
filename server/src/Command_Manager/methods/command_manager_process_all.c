/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager_process_all
*/

#include "command_manager.h"
#include "utils.h"


/****************************************************************************/
/*                                                                          */
/*                       MANAGE AND EXECUTE COMMAND                         */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Builds a full command string with a prefix based on client type.
 *
 * @param dest Destination buffer for the resulting command string.
 * @param size Size of the destination buffer.
 * @param type Type of the client (CLIENT_GUI or other).
 * @param cmd  Command name to append.
 */
static void build_full_command(char *dest,
    size_t size, client_type_t type, const char *cmd)
{
    const char *prefix = (type == CLIENT_GUI) ? "gui" : "ia";

    snprintf(dest, size, "command_%s_%s", prefix, cmd);
    dest[size - 1] = '\0';
}

/**
 * @brief Log that a command is still waiting to be executed.
 *
 * @param client Pointer to the client.
 * @param cmd Name of the command.
 * @param ticks_remaining Number of ticks remaining before execution.
 */
static void log_waiting(client_t *client, const char *cmd, int ticks_remaining)
{
    console_log(LOG_INFO,
        "Client %d | Waiting: %s (%d ticks left)",
        client->fd, cmd, ticks_remaining);
}

/**
 * @brief Log that a command is now being executed.
 *
 * @param client Pointer to the client.
 * @param cmd Name of the command.
 */
static void log_executing(client_t *client, const char *cmd)
{
    console_log(LOG_SUCCESS,
        "Client %d | Executing: %s",
        client->fd, cmd);
}

static gui_command_type_t detect_gui_command_type(const char *cmd)
{
    if (!cmd)
        return GUI_CMD_NONE;
    if (strncmp(cmd, "Forward", 7) == 0)
        return GUI_CMD_PMV;
    if (strncmp(cmd, "Fork", 4) == 0)
        return GUI_CMD_PFK;
    if (strncmp(cmd, "Eject", 5) == 0)
        return GUI_CMD_PEJ;
    return GUI_CMD_NONE;
}

/**
 * @brief Update the last_tick_checked of the next queued command.
 *
 * @param client Pointer to the client.
 * @param current_tick Current game tick.
 */
static void update_next_command_tick(client_t *client,
    int current_tick)
{
    queued_command_t *next = client_peek_command(client);

    if (next && next->ticks_remaining > 0)
        next->last_tick_checked = current_tick + 1;
    if (!next)
        return;
    next->gui_check = detect_gui_command_type(next->content);
}

/**
 * @brief Execute a command that is ready (ticks_remaining == 0).
 *
 * Resolves the command name, emits the corresponding event,
 * dequeues the command, and updates tick tracking for the next one.
 *
 * @param mgr Pointer to the command manager.
 * @param client Pointer to the client executing the command.
 * @param cmd Pointer to the command being executed.
 * @param current_tick Current tick count of the game.
 */
static void execute_ready_command(server_t *server,
    client_t *client, queued_command_t *cmd, int current_tick)
{
    char built[BUFFER_COMMAND_SIZE] = {0};
    char cmd_name[BUFFER_SIZE] = {0};
    event_type_t id;

    extract_command_name(cmd->content, cmd_name, sizeof(cmd_name));
    build_full_command(built, sizeof(built), client->type, cmd_name);
    id = event_type_from_string(built, EVENT_CMD_NAME,
        sizeof(EVENT_CMD_NAME) / sizeof(EVENT_CMD_NAME[0]));
    EMIT(server->command_manager->dispatcher, id, client);
    client_dequeue_command(client, NULL);
    update_next_command_tick(client, current_tick);
}

/**
 * @brief Handle tick countdown for a client's command.
 *
 * Decrements ticks and logs state or triggers execution if ready.
 *
 * @param mgr Pointer to the command manager.
 * @param client Pointer to the client.
 * @param cmd Pointer to the command.
 * @param current_tick Current game tick.
 */
static void handle_client_command(server_t *server,
    client_t *client, queued_command_t *cmd, int current_tick)
{
    char cmd_name[BUFFER_SIZE] = {0};
    int ticks_elapsed = current_tick - cmd->last_tick_checked;

    if (current_tick <= cmd->last_tick_checked)
        return;
    extract_command_name(cmd->content, cmd_name, sizeof(cmd_name));
    cmd->ticks_remaining -= ticks_elapsed;
    cmd->last_tick_checked = current_tick;
    if (cmd->ticks_remaining > 0)
        log_waiting(client, cmd_name, cmd->ticks_remaining);
    else {
        log_executing(client, cmd->content);
        execute_ready_command(server, client, cmd, current_tick);
    }
}

/**
 * @brief Process all queued commands for every active client.
 *
 * Executes commands when ready or updates their remaining ticks.
 *
 * @param mgr Pointer to the command manager.
 * @param server Pointer to the server instance.
 * @param current_tick Current game tick.
 */
void process_all(command_manager_t *mgr, server_t *server, int current_tick)
{
    list_node_t *node = NULL;
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    if (!mgr || !server || !server->clients)
        return;
    for (node = server->clients->head; node; node = node->next) {
        client = node->data;
        if (!client || !client->connected || client->stuck)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        if (cmd->ticks_remaining == 0)
            execute_ready_command(server, client, cmd, current_tick);
        else
            handle_client_command(server, client, cmd, current_tick);
    }
}
