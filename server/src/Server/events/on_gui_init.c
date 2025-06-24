/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_gui_init
*/

#include "client.h"
#include "game.h"
#include "list.h"
#include "server.h"
#include "shared.h"

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

    for (list_node_t *node = server->game->eggs->head;
        node; node = node->next) {
        egg = node->data;
        if (!egg)
            continue;
        event = malloc(sizeof(game_event_t));
        if (!event)
            continue;
        event->type = EVENT_EGG_LAID;
        event->data.egg.egg_id = egg->id;
        event->data.egg.player = egg->player;
        event->data.egg.x = egg->x;
        event->data.egg.y = egg->y;
        event->data.egg.team_name = egg->team_name;
        EMIT(server->command_manager->dispatcher, EVENT_GUI_ENW, event);
        free(event);
    }
}

/**
 * @brief Emits GUI player events for all players in the game.
 *
 * Iterates through the list of players and emits GUI events for each,
 * informing the GUI about player positions and inventories.
 *
 * @param server Pointer to the server instance.
 */
static void emit_gui_players(server_t *server)
{
    int index;
    player_t *player = NULL;
    list_t *players = server->game->players;

    for (index = 0; index < server->game->players->size; index++) {
        player = players->methods->index(players, index);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PNW,
            player->client);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PIN,
            player);
    }
}

/**
 * @brief Emits GUI incantation events for all ongoing incantations.
 *
 * Iterates through the list of incantations and emits GUI events for each.
 *
 * @param server Pointer to the server instance.
 */
static void emit_gui_incantations(server_t *server)
{
    game_event_t event;
    int index;
    list_t *list = server->game->incantations;
    incantation_t *incantation = NULL;

    event.type = EVENT_GUI_PIC;
    for (index = 0; index < list->size; ++index) {
        incantation = list->methods->index(list, index);
        event.data.incantation.x = incantation->x;
        event.data.incantation.y = incantation->y;
        event.data.incantation.participants = incantation->participants;
        event.data.incantation.success = false;
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PIC, &event);
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
    EMIT(server->command_manager->dispatcher, CMD_GUI_MSZ, client);
    EMIT(server->command_manager->dispatcher, CMD_GUI_SGT, client);
    EMIT(server->command_manager->dispatcher, CMD_GUI_MCT, client);
    EMIT(server->command_manager->dispatcher, CMD_GUI_TNA, client);
    emit_gui_egg_events(server);
    emit_gui_players(server);
    emit_gui_incantations(server);
}
