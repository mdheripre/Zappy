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
 * Calls each player's update method with the current game state.
 *
 * @param self Pointer to the game instance.
 */
void update_players(game_t *self)
{
    list_node_t *node = NULL;
    player_t *player;

    if (!self || !self->players)
        return;
    node = self->players->head;
    while (node) {
        player = node->data;
        if (player && player->methods && player->methods->update)
            player->methods->update(player, self);
        node = node->next;
    }
}
