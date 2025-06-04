/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_destroy
*/

#include "game.h"

void game_destroy(game_t *game)
{
    if (!game)
        return;
    for (int y = 0; y < game->height; y++)
        free(game->map[y]);
    free(game->map);
}
