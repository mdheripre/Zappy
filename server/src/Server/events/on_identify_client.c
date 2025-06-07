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

/**
 * @brief Checks if another GUI client is already connected.
 *
 * Iterates through the list of connected clients to determine whether
 * a GUI client other than the given one is already present.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the current client being verified.
 * @return true if another GUI is already connected, false otherwise.
 */
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

/**
 * @brief Handles the first command sent by a client to identify itself.
 *
 * Parses the first message sent by the client. If it's "GRAPHIC", ensures
 * no other GUI is already connected. Then emits the corresponding init
 * event ("gui_init" or "ia_init") and dequeues the command.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the client (cast from void).
 */
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
        reject_client(server, client, "Rejected GUI: already connected");
        return;
    }
    emit_identify_event(server, client, cleaned);
    client_dequeue_command(client, NULL);
}
