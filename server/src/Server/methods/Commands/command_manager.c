/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager
*/

#include "server.h"
#include "dispatcher.h"
#include "shared.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          REGISTER COMMAND                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Registers all available commands with the server's dispatcher.
 *
 * @param server Pointer to the server structure.
 */
void command_manager_register_all(server_t *server)
{
    REGISTER(server->dispatcher, "command_ia_Forward",
        handle_command_forward, NULL);
}

/****************************************************************************/
/*                                                                          */
/*                         FORMAT COMMAND                                   */
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

/****************************************************************************/
/*                                                                          */
/*                        PROCESS IDENTIFY                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Processes identification for all undefined clients.
 *
 * Iterates through all connected clients with undefined type,
 * checks if they have a queued command, and emits a "client_identify" event.
 *
 * @param server Pointer to the server structure.
 */
void command_process_identify(server_t *server)
{
    client_t *client = NULL;
    queued_command_t *cmd = NULL;
    int i = 0;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client->connected || client->type != CLIENT_UNDEFINED)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        EMIT(server->dispatcher, "client_identify", client);
    }
}

/****************************************************************************/
/*                                                                          */
/*                       MANAGE AND EXECUTE COMMAND                         */
/*                                                                          */
/****************************************************************************/


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
static void execute_command(server_t *server,
    client_t *client, queued_command_t *cmd, float delta)
{
    char built[BUFFER_COMMAND_SIZE] = {0};

    cmd->time_remaining -= delta;
    console_log(LOG_INFO, "Client %d command: \"%s\" (%.2fs left)",
    client->fd, cmd->content, cmd->time_remaining);
    if (cmd->time_remaining > 0.0f)
        return;
    build_full_command(built, sizeof(built), client->type, cmd->content);
    EMIT(server->dispatcher, built, client);
    client_dequeue_command(client, NULL);
}

/**
 * @brief Processes and executes the next queued command for all connected
 * IA clients.
 *
 * @param server Pointer to the server structure.
 * @param delta Time elapsed since last update, used for command execution.
 */
void command_process_all(server_t *server, float delta)
{
    int i = 0;
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client || !client->connected)
            continue;
        if (client->type != CLIENT_IA)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        execute_command(server, client, cmd, delta);
    }
}
