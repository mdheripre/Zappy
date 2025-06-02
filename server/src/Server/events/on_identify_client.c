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

static void emit_identify_event(server_t *server,
    client_t *client, const char *message)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));
    const char *event = strcmp(message, "GRAPHIC") == 0 ? "gui_init"
        : "ia_init";

    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(message);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, event, payload);
    free(payload->message);
    free(payload);
}

void on_client_identify(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    queued_command_t *cmd = NULL;
    char cleaned[BUFFER_COMMAND_SIZE] = {0};

    if (!server || !client || client->type != CLIENT_UNDEFINED)
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
    emit_identify_event(server, client, cleaned);
    client_dequeue_command(client, NULL);
}
