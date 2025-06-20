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


/**
 * @brief Creates a new player based on a given configuration.
 *
 * Allocates and initializes a new player structure using values from the
 * provided configuration. Initializes the inventory to zero and sets the
 * initial level to 1. The player's team name is duplicated.
 *
 * @param config Player configuration structure.
 * @return Pointer to the new player, or NULL on allocation failure.
 */
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
    player->nbr_tick = 0;
    player->team_name = strdup(config.team_name);
    if (!player->team_name) {
        free(player);
        return NULL;
    }
    player->methods = &PLAYER_METHODS;
    memset(player->inventory, 0, sizeof(player->inventory));
    player->inventory[RESOURCE_FOOD] = 9;
    return player;
}
