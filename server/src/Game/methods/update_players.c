/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** update_players
*/

#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Update all players in the game.
 *
 * Calls each player's update method, passing the elapsed ticks.
 *
 * @param self Pointer to the game instance.
 * @param ticks Number of ticks since the last update.
 */
void update_players(game_t *self, int ticks)
{
    player_t *player = NULL;

    if (!self || !self->players)
        return;
    for (list_node_t *n = self->players->head; n; n = n->next) {
        player = n->data;
        if (player)
            player->methods->update(player, self, ticks);
    }
}
