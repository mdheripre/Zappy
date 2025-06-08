/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** move
*/

#include "player.h"
#include "utils.h"

void player_move(player_t *self, int dx, int dy)
{
    if (!self)
        return;
    self->x += dx;
    self->y += dy;
}
