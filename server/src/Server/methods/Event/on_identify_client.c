/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_identify_client
*/

#include "server.h"
#include "utils.h"


/****************************************************************************/
/*                                                                          */
/*                        IDENTIFY CLIENT                                   */
/*                                                                          */
/****************************************************************************/

static void dispatch_type(client_t *client, char *cleaned)
{
    if (strcmp(cleaned, "GRAPHIC") == 0) {
        client->type = CLIENT_GUI;
        console_log(LOG_SUCCESS, "Client %d is GUI", client->fd);
    } else {
        client->type = CLIENT_IA;
        console_log(LOG_SUCCESS, "Client %d is IA (team: \"%s\")",
            client->fd, cleaned);
    }
}

/**
 * @brief Handles the client identification event.
 *
 * This function is called when a client sends an identification command.
 * It checks if the client is undefined, processes the command, and
 * identifies the client type based on the command content.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the client instance.
 */
void on_client_identify(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    queued_command_t *cmd = NULL;
    char cleaned[BUFFER_COMMAND_SIZE] = {0};

    if (!client || !server || client->type != CLIENT_UNDEFINED)
        return;
    cmd = client_peek_command(client);
    if (!cmd)
        return;
    strncpy(cleaned, cmd->content, BUFFER_COMMAND_SIZE - 1);
    cleaned[BUFFER_COMMAND_SIZE - 1] = '\0';
    strip_linefeed(cleaned);
    dispatch_type(client, cleaned);
    client_dequeue_command(client, NULL);
}
