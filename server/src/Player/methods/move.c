/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** move
*/

#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                           PLAYER METHOD                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Move the player by the given delta.
 *
 * @param self Pointer to the player.
 * @param dx Horizontal offset.
 * @param dy Vertical offset.
 */
void player_move(player_t *self, int dx, int dy)
{
    if (!self)
        return;
    self->x += dx;
    self->y += dy;
}
