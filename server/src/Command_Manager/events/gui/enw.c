/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Formats the ENW (egg new) event message for the GUI.
 *
 * @param buffer The buffer to write the message into.
 * @param size The size of the buffer.
 * @param event The game event containing egg information.
 */
static void format_enw_message(char *buffer, size_t size,
    const game_event_t *event)
{
    snprintf(buffer, size, "enw #%d #%d %d %d\n",
        event->data.egg.egg_id, event->data.egg.player_id,
        event->data.egg.x, event->data.egg.y);
}

/**
 * @brief Prepares the response payload for the ENW event.
 *
 * @param server The server context.
 * @param event The game event data.
 * @return response_payload_t* The prepared payload, or NULL on failure.
 */
static response_payload_t *prepare_enw_payload(server_t *server,
    game_event_t *event)
{
    client_t *gui = NULL;
    response_payload_t *payload = NULL;
    char buffer[BUFFER_SIZE] = {0};

    if (!server || !event)
        return NULL;
    gui = server->vtable->get_gui(server);
    if (!gui)
        return NULL;
    format_enw_message(buffer, sizeof(buffer), event);
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return NULL;
    payload->client = gui;
    payload->message = strdup(buffer);
    if (!payload->message) {
        free(payload);
        return NULL;
    }
    return payload;
}

/**
 * @brief Handles the ENW event for the GUI by emitting the response.
 *
 * @param ctx The server context.
 * @param data The event data.
 */
void handle_gui_enw(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload = prepare_enw_payload(server, event);

    if (!payload)
        return;
    EMIT(server->dispatcher, "send_response", payload);
}
