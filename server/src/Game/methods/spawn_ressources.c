/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** spawn_ressources
*/

#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Resource spawn density per tile for each resource type.
 *
 * Used to compute how many of each resource to spawn on the map.
 */
static const double RESOURCE_DENSITY[RESOURCE_COUNT] = {
    [RESOURCE_FOOD] = 0.5,
    [RESOURCE_LINEMATE] = 0.3,
    [RESOURCE_DERAUMERE] = 0.15,
    [RESOURCE_SIBUR] = 0.1,
    [RESOURCE_MENDIANE] = 0.1,
    [RESOURCE_PHIRAS] = 0.08,
    [RESOURCE_THYSTAME] = 0.05
};

/**
 * @brief Count the total amount of a specific resource on the map.
 *
 * @param game Pointer to the game instance.
 * @param type Resource type index.
 * @return Total number of units of the resource found.
 */
static int count_existing_resource(game_t *game, int type)
{
    int total = 0;

    for (int y = 0; y < game->height; y++) {
        for (int x = 0; x < game->width; x++) {
            total += game->map[y][x].resources[type];
        }
    }
    return total;
}

/**
 * @brief Queue a tile update event for a specific coordinate.
 *
 * @param game Pointer to the game instance.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 */
void add_tile_update_event(game_t *game, int x, int y)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return;
    event->type = EVENT_RESP_TILE_UPDATED;
    event->data.tile.x = x;
    event->data.tile.y = y;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, event);
}

/**
 * @brief Spawn a given amount of a resource type randomly on the map.
 *
 * Triggers tile update events for each spawned resource.
 *
 * @param game Pointer to the game instance.
 * @param type Resource type index.
 * @param to_spawn Number of resources to spawn.
 */
static void spawn_resource_type(game_t *game, int type, int to_spawn)
{
    int x;
    int y;

    for (int i = 0; i < to_spawn; i++) {
        x = rand() % game->width;
        y = rand() % game->height;
        game->map[y][x].resources[type]++;
        add_tile_update_event(game, x, y);
    }
}

/**
 * @brief Ensure minimum resource count across the map.
 *
 * Spawns missing resources according to density configuration.
 *
 * @param game Pointer to the game instance.
 */
void spawn_resources(game_t *game)
{
    int total_tiles = game->width * game->height;
    int max_per_type = 0;
    int current = 0;
    int to_spawn = 0;

    for (int type = 0; type < RESOURCE_COUNT; type++) {
        max_per_type = (int)(RESOURCE_DENSITY[type] * total_tiles);
        if (max_per_type == 0)
            max_per_type = 1;
        current = count_existing_resource(game, type);
        to_spawn = max_per_type - current;
        if (to_spawn <= 0)
            continue;
        spawn_resource_type(game, type, to_spawn);
    }
}
