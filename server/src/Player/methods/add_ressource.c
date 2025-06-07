/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** add_ressource
*/

#include "player.h"

void player_add_resource(player_t *self, int type, int amount)
{
    if (!self || type < 0 || type >= INVENTORY_SIZE)
        return;
    self->inventory[type] += amount;
}
