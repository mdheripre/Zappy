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
    return server->gui && server->gui != client;
}

/**
 * @brief Emits an identification event based on the message content.
 *
 * Determines the correct event type ("gui_init" or "ia_init") based
 * on the message, wraps the message and client into a payload, and
 * emits it through the server dispatcher.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the identifying client.
 * @param message Message used to determine the client type.
 */
static void emit_identify_event(server_t *server,
    client_t *client, const char *message)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));
    const char *event = strcmp(message, "GRAPHIC") == 0 ? "gui_init"
        : "ia_init";

    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(strncmp(message, "TEAM-", 5) == 0 ?
        message + 5 : message);
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
    char cleaned[CLIENT_BUFFER_SIZE] = {0};

    if (!server || !client || client->type != CLIENT_UNDEFINED)
        return;
    cmd = client_peek_command(client);
    if (!cmd)
        return;
    strncpy(cleaned, cmd->content, CLIENT_BUFFER_SIZE - 1);
    cleaned[CLIENT_BUFFER_SIZE - 1] = '\0';
    strip_linefeed(cleaned);
    client_dequeue_command(client, NULL);
    if (strcmp(cleaned, "GRAPHIC") == 0 && check_second_gui(server, client)) {
        reject_client(server, client, "Rejected GUI: already connected");
        return;
    }
    emit_identify_event(server, client, cleaned);
}
