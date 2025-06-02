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

static bool check_second_gui(server_t *server, client_t *client)
{
    client_t *other = NULL;

    for (int i = 0; i < server->client_count; i++) {
        other = &server->clients[i];
        if (other->connected && other != client &&
            other->type == CLIENT_GUI)
            return true;
    }
    return false;
}

static void reject_client(server_t *server, client_t *client)
{
    write(client->fd, "ko\n", 3);
    for (int i = 0; i < server->client_count; i++) {
        if (&server->clients[i] == client) {
            remove_client(server, i);
            return;
        }
    }
}

static void dispatch_client_type(client_t *client, const char *cleaned,
    server_t *server)
{
    if (strcmp(cleaned, "GRAPHIC") == 0)
        EMIT(server->dispatcher, "gui_init", client);
    else {
        client->type = CLIENT_IA;
        console_log(LOG_SUCCESS, "Client %d is IA (team: \"%s\")",
            client->fd, cleaned);
    }
}

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
    if (strcmp(cleaned, "GRAPHIC") == 0 && check_second_gui(server, client)) {
        console_log(LOG_WARNING, "Rejected GUI: already connected");
        reject_client(server, client);
        return;
    }
    dispatch_client_type(client, cleaned, server);
    client_dequeue_command(client, NULL);
}
