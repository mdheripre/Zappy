/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_gui_init
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                         GUI INITIALISATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emits GUI egg events for all eggs in the game.
 *
 * Iterates through the list of eggs and emits a GUI event for each,
 * informing the GUI about existing eggs.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the GUI client.
 */
static void emit_gui_egg_events(server_t *server)
{
    egg_t *egg = NULL;
    game_event_t *event = NULL;

    for (list_node_t *node = server->game->eggs->head; node;
        node = node->next) {
        egg = node->data;
        if (!egg)
            continue;
        event = malloc(sizeof(game_event_t));
        if (!event)
            continue;
        event->type = GAME_EVENT_RESPONSE_EGG_LAID;
        event->data.egg.egg_id = egg->id;
        event->data.egg.player_id = egg->player_id;
        event->data.egg.x = egg->x;
        event->data.egg.y = egg->y;
        event->data.egg.team_name = egg->team_name;
        EMIT(server->command_manager->dispatcher, "gui_enw", event);
        free(event);
    }
}

/**
 * @brief Initializes a GUI client after connection.
 *
 * Sets the client type to GUI, clears its player pointer, and emits
 * the MSZ, SGT, and MCT commands to initialize the GUI with map size,
 * time unit, and full map content.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the response payload containing the client.
 */
void on_gui_init(void *ctx, void *data)
{
    server_t *server = ctx;
    response_payload_t *payload = data;
    client_t *client = payload->client;

    if (!server || !client)
        return;
    client->type = CLIENT_GUI;
    client->player = NULL;
    server->gui = client;
    console_log(LOG_SUCCESS, "Client %d is GUI", client->fd);
    EMIT(server->command_manager->dispatcher, "command_gui_msz", client);
    EMIT(server->command_manager->dispatcher, "command_gui_sgt", client);
    EMIT(server->command_manager->dispatcher, "command_gui_mct", client);
    EMIT(server->command_manager->dispatcher, "command_gui_tna", client);
    emit_gui_egg_events(server);
}
