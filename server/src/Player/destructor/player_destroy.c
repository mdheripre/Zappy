/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_destroy
*/

#include "player.h"

void player_destroy(player_t *self)
{
    if (!self)
        return;
    free(self->team_name);
}
