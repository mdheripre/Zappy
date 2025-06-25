/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_player_died
*/

#include "command_manager.h"
#include "game.h"
#include "player.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Notify the player and GUI of the player's death.
 *
 * Sends "dead" to the client and emits a GUI PDI (Player Death) event.
 *
 * @param server Pointer to the server instance.
 * @param player Pointer to the player who died.
 */
static void notify_player_death(server_t *server, player_t *player)
{
    client_t *client = player ? player->client : NULL;

    if (client)
        dprintf(client->fd, "dead\n");
    EMIT(server->command_manager->dispatcher, EVENT_GUI_PDI, player);
}

/**
 * @brief Handle the death of a player and clean up.
 *
 * Notifies the player and GUI, removes the player from the game,
 * and disconnects the client if present.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the death event.
 */
void on_response_player_died(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_died.player;
    client_t *client = player ? player->client : NULL;

    if (!server || !player)
        return;
    notify_player_death(server, player);
    server->game->players->methods->remove(server->game->players, player);
    if (client)
        server->vtable->remove_client(server, client);
}
