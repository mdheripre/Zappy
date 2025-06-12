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


static void add_tile_update_event(game_t *game, int x, int y)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return;
    event->type = GAME_EVENT_RESPONSE_TILE_UPDATED;
    event->data.tile.x = x;
    event->data.tile.y = y;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, event);
}

/**
 * @brief Spawn resources randomly on the game map based on density.
 *
 * @param self Pointer to the game instance.
 */
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
            add_tile_update_event(self, x, y);
        }
    }
}
