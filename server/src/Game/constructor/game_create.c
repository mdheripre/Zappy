/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_create
*/

#include "game.h"
#include "list.h"
#include "shared.h"

static const game_methods_t GAME_METHODS = {
    .tick = game_tick,
    .add_event = game_add_event,
    .pop_event = game_pop_event,
    .dispatch_events = game_dispatch_events,
    .update = game_update,
    .count_team_members = count_team_members,
};

static void game_init_tile(tile_t *tile, int x, int y)
{
    tile->x = x;
    tile->y = y;
    for (int r = 0; r < RESOURCE_COUNT; r++)
        tile->resources[r] = 0;
}

static bool game_init_map(game_t *game)
{
    game->map = malloc(sizeof(tile_t *) * game->height);
    if (!game->map)
        return false;
    for (int y = 0; y < game->height; y++) {
        game->map[y] = malloc(sizeof(tile_t) * game->width);
        if (!game->map[y])
            return false;
        for (int x = 0; x < game->width; x++)
            game_init_tile(&game->map[y][x], x, y);
    }
    return true;
}

static void free_players(void *data)
{
}

static bool game_init_lists(game_t *game)
{
    game->players = NEW(list, free_players);
    game->eggs = NEW(list, NULL);
    game->incantations = NEW(list, NULL);
    game->event_queue = NEW(list, free);
    return game->players && game->eggs && game->event_queue &&
    game->incantations;
}

game_t *game_create(config_game_t *config)
{
    game_t *game = malloc(sizeof(game_t));

    if (!config || !game)
        return NULL;
    game->width = config->width;
    game->height = config->height;
    game->frequency = config->frequency;
    game->team_size = config->team_size;
    game->team_name = config->team_name;
    game->last_tick_time = 0;
    game->started = false;
    game->methods = &GAME_METHODS;
    game->dispatcher = NEW(dispatcher, NULL);
    if (!game->dispatcher)
        return NULL;
    if (!game_init_map(game) || !game_init_lists(game))
        return NULL;
    return game;
}
