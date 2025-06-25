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
 * @brief Checks if there is a second GUI client connected to the server.
 *
 * @param server Pointer to the server structure.
 * @param client Pointer to the current client.
 * @return true if another GUI client is connected, false otherwise.
 */
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
    event_type_t event = (strcmp(message, "GRAPHIC") == 0)
        ? EVENT_GUI_INIT : EVENT_IA_INIT;

    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(strncmp(message, "TEAM-", 5) == 0
        ? message + 5 : message);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, event, payload);
    free(payload->message);
    free(payload);
}

/**
 * @brief Handles the identification process for a connecting client.
 *
 * This function checks if the client is undefined and processes its
 * first command to determine its type (e.g., GUI or player).
 * It rejects duplicate GUI connections and emits an identification event
 * for valid clients.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the client data (client_t).
 */
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
