/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_player_eat
*/

#include "client.h"
#include "server.h"
#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the response when a player eats.
 *
 * Emits an event to notify the GUI about the player's inventory update.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event data.
 */
void on_response_player_eat(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.generic_response.client->player;

    if (!server || !player)
        return;
    EMIT(server->command_manager->dispatcher, EVENT_GUI_PIN, player);
}
