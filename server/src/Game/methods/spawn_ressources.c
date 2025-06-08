/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** spawn_ressources
*/

#include "game.h"

static const double RESOURCE_DENSITY[RESOURCE_COUNT] = {
    [RESOURCE_FOOD] = 0.5,
    [RESOURCE_LINEMATE] = 0.3,
    [RESOURCE_DERAUMERE] = 0.15,
    [RESOURCE_SIBUR] = 0.1,
    [RESOURCE_MENDIANE] = 0.1,
    [RESOURCE_PHIRAS] = 0.08,
    [RESOURCE_THYSTAME] = 0.05
};

void spawn_resources(game_t *self)
{
    int total_tiles = self->width * self->height;
    int count[RESOURCE_COUNT];
    int x;
    int y;

    for (int r = 0; r < RESOURCE_COUNT; r++) {
        count[r] = (int)(RESOURCE_DENSITY[r] * total_tiles);
        if (count[r] == 0)
            count[r] = 1;
    }
    for (int r = 0; r < RESOURCE_COUNT; r++) {
        for (int i = 0; i < count[r]; i++) {
            x = rand() % self->width;
            y = rand() % self->height;
            self->map[y][x].resources[r]++;
        }
    }
}
