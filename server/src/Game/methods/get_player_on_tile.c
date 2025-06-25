/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** get_player_on_tile
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Retrieves a list of players on a specific tile and level.
 *
 * Iterates through all players in the game and collects those who are alive,
 * located at the specified (x, y) coordinates, and at the given level.
 *
 * @param game Pointer to the game structure.
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @param level Level to match.
 * @return list_t* List of matching players, or NULL on error.
 */
list_t *get_players_on_tile(game_t *game, int x, int y, int level)
{
    list_t *participants = NEW(list, NULL);
    player_t *p = NULL;

    if (!game || !participants)
        return NULL;
    for (list_node_t *node = game->players->head; node; node = node->next) {
        p = node->data;
        if (p && p->is_alive && p->x == x && p->y == y && p->level == level)
            participants->methods->push_back(participants, p);
    }
    return participants;
}
