/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_create
*/

#include "player.h"
#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                              CONSTRUCTOR                                 */
/*                                                                          */
/****************************************************************************/

static const player_methods_t PLAYER_METHODS = {
    .move = player_move,
    .die = player_die,
    .add_resource = player_add_resource,
    .remove_resource = player_remove_resource,
    .update = player_update,
};

static void player_init(player_t *player, player_config_t config)
{
    player->id = config.id;
    player->x = config.x;
    player->y = config.y;
    player->orientation = config.orientation;
    player->level = 1;
    player->client = config.client;
    player->is_alive = true;
    player->nbr_tick = 126;
    player->team_name = strdup(config.team_name);
    player->methods = &PLAYER_METHODS;
    memset(player->inventory, 0, sizeof(player->inventory));
    player->inventory[RESOURCE_FOOD] = 10;
}

player_t *player_create(player_config_t config)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player_init(player, config);
    if (!player->team_name) {
        free(player);
        return NULL;
    }
    return player;
}
