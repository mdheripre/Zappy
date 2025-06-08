/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** remove_ressource
*/

#include "player.h"

void player_remove_resource(player_t *self, int type, int amount)
{
    if (!self || type < 0 || type >= INVENTORY_SIZE)
        return;
    self->inventory[type] -= amount;
    if (self->inventory[type] < 0)
        self->inventory[type] = 0;
}
