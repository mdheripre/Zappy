/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_egg_laid
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the response when an egg is laid by a player.
 *
 * Sends an "ok" message to the player's client, increments the maximum number
 * of players in the game, and emits an event for GUI notification.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the event data (game_event_t).
 */
void on_response_egg_laid(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.egg.player;

    if (!server || !event || !player || !player->client)
        return;
    dprintf(player->client->fd, "ok\n");
    server->game->max_players++;
    EMIT(server->command_manager->dispatcher, EVENT_GUI_ENW, event);
}
