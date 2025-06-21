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
 * @brief Notify the player and GUI about the player's death.
 *
 * Sends "dead" to the player and emits the "gui_pdi" event.
 *
 * @param server Pointer to the server.
 * @param player Pointer to the player who died.
 */
static void notify_player_death(server_t *server, player_t *player)
{
    client_t *client = get_client_by_player(server, player);

    if (client)
        dprintf(client->fd, "dead\n");
    EMIT(server->command_manager->dispatcher, "gui_pdi", player);
}

/**
 * @brief Handle a player's death and remove them from the server.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the death event (game_event_t *).
 */
void on_response_player_died(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = NULL;
    client_t *client = NULL;

    if (!server || !event)
        return;
    player = find_player_by_id(server->game,
        event->data.player_died.player_id);
    if (!player)
        return;
    notify_player_death(server, player);
    client = get_client_by_player(server, player);
    server->game->players->methods->remove(server->game->players, player);
    if (client)
        server->vtable->remove_client(server, client);
}
