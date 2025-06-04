/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_destroy
*/

#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                              DESTRUCTOR                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Frees the memory allocated for the game map.
 *
 * Deallocates all rows of the game's 2D tile map and then frees the map
 * itself. Does nothing if the game pointer is NULL. Other internal structures
 * are not freed here and must be handled separately.
 *
 * @param game Pointer to the game instance to destroy.
 */
void game_destroy(game_t *game)
{
    if (!game)
        return;
    for (int y = 0; y < game->height; y++)
        free(game->map[y]);
    free(game->map);
}
