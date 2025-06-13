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
 * @brief Extracts the command name from a queued command content.
 *
 * @param content The content of the queued command.
 * @param out Buffer to store the extracted command name.
 * @param size Size of the output buffer.
 */
static void execute_ready_command(command_manager_t *self,
    client_t *client, queued_command_t *cmd)
{
    char built[BUFFER_COMMAND_SIZE] = {0};
    char cmd_name[BUFFER_SIZE] = {0};

    extract_command_name(cmd->content, cmd_name, sizeof(cmd_name));
    build_full_command(built, sizeof(built), client->type, cmd_name);
    EMIT(self->dispatcher, built, client);
    client_dequeue_command(client, NULL);
}

/**
 * @brief Process a command if its remaining time is up.
 *
 * Logs progress and calls execution when ticks_remaining reaches zero.
 *
 * @param self Pointer to the command manager.
 * @param client Pointer to the client.
 * @param cmd Pointer to the queued command.
 * @param ticks Number of ticks passed since last update.
 */
static void process_command_if_ready(command_manager_t *self,
    client_t *client, queued_command_t *cmd, int ticks)
{
    char cmd_name[BUFFER_SIZE] = {0};

    extract_command_name(cmd->content, cmd_name, sizeof(cmd_name));
    cmd->ticks_remaining -= ticks;
    if (cmd->ticks_remaining > 0) {
        console_log(LOG_INFO,
            "Client %d | Waiting: %s (%d ticks left)",
            client->fd, cmd_name, cmd->ticks_remaining);
    } else {
        console_log(LOG_SUCCESS,
            "Client %d | Executing: %s",
            client->fd, cmd_name);
        execute_ready_command(self, client, cmd);
    }
}

/**
 * @brief Update and process commands for all connected clients.
 *
 * Skips clients that are disconnected or stuck.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 * @param ticks Number of ticks passed since last update.
 */
void process_all(command_manager_t *self, server_t *server, int ticks)
{
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    if (!self || !server)
        return;
    for (int i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client || !client->connected || client->stuck)
            continue;
        cmd = client_peek_command(client);
        if (cmd && (cmd->scheduled_tick != server->game->tick_counter - ticks
            || cmd->ticks_remaining <= 0))
            process_command_if_ready(self, client, cmd, ticks);
    }
}
