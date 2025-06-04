/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_create
*/

#include "player.h"

player_t *player_create(player_config_t config)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->id = config.id;
    player->x = config.x;
    player->y = config.y;
    player->orientation = config.orientation;
    player->level = 1;
    player->is_alive = true;
    player->team_name = strdup(config.team_name);
    if (!player->team_name) {
        free(player);
        return NULL;
    }
    memset(player->inventory, 0, sizeof(player->inventory));
    return player;
}
