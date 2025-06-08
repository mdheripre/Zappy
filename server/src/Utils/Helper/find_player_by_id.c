/*
** EPITECH PROJECT, 2025
** server
** File description:
** find_player_by_id
*/

#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Find a player in the game by their ID.
 *
 * @param game Pointer to the game instance.
 * @param player_id ID of the player to find.
 * @return Pointer to the player, or NULL if not found.
 */
player_t *find_player_by_id(game_t *game, int player_id)
{
    player_t *player = NULL;

    if (!game || !game->players)
        return NULL;
    for (list_node_t *node = game->players->head; node; node = node->next) {
        player = (player_t *)node->data;
        if (player && player->id == player_id)
            return player;
    }
    return NULL;
}
