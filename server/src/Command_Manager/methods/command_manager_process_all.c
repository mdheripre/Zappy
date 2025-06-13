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
 * @brief Processes a queued command for a client if it is
 *        ready to be executed.
 *
 * This function checks the time remaining for the command and executes it
 * if the time has elapsed. It also logs the command execution.
 *
 * @param self Pointer to the command manager instance.
 * @param client Pointer to the client that owns the command.
 * @param cmd Pointer to the queued command to process.
 * @param delta Time elapsed since last update, used for command execution.
 */
static void process_command_if_ready(command_manager_t *self,
    client_t *client, queued_command_t *cmd, float delta)
{
    char cmd_name[BUFFER_SIZE] = {0};

    extract_command_name(cmd->content, cmd_name, sizeof(cmd_name));
    cmd->time_remaining -= delta;
    console_log(LOG_INFO, "Client %d command: \"%s\" (%.2fs left)",
        client->fd, cmd_name, cmd->time_remaining);
    if (cmd->time_remaining <= 0.0f)
        execute_ready_command(self, client, cmd);
}

/**
 * @brief Processes and executes the next queued command for all connected
 * IA clients.
 *
 * @param server Pointer to the server structure.
 * @param delta Time elapsed since last update, used for command execution.
 */
void process_all(command_manager_t *self, server_t *server, float delta)
{
    int i = 0;
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client || !client->connected || client->stuck)
            continue;
        cmd = client_peek_command(client);
        if (cmd)
            process_command_if_ready(self, client, cmd, delta);
    }
}
