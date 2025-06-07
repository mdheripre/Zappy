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
 * @brief Executes a queued command for a client if its timer has expired.
 *
 * Decrements the command's remaining time by delta. If the timer reaches
 * zero, builds the full command, emits it to the dispatcher,
 * and dequeues the command.
 *
 * @param server Pointer to the server structure.
 * @param client Pointer to the client structure.
 * @param cmd Pointer to the queued command.
 * @param delta Time elapsed since last call (in seconds).
 */
static void execute_command(command_manager_t *self,
    client_t *client, queued_command_t *cmd, float delta)
{
    char built[BUFFER_COMMAND_SIZE] = {0};

    cmd->time_remaining -= delta;
    console_log(LOG_INFO, "Client %d command: \"%s\" (%.2fs left)",
    client->fd, cmd->content, cmd->time_remaining);
    if (cmd->time_remaining > 0.0f)
        return;
    build_full_command(built, sizeof(built), client->type, cmd->content);
    EMIT(self->dispatcher, built, client);
    client_dequeue_command(client, NULL);
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
        if (!client || !client->connected || client->type != CLIENT_IA
            || !client->stuck)
            continue;
        if (client->type != CLIENT_IA)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        execute_command(self, client, cmd, delta);
    }
}
