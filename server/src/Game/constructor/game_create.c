/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_create
*/

#include "game.h"
#include "list.h"
#include "utils.h"
#include "shared.h"

/****************************************************************************/
/*                                                                          */
/*                        METHODS INITIALIZATION                            */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Table of game methods used to operate on the game state.
 *
 * Contains function pointers for game logic operations.
 */
static const game_methods_t GAME_METHODS = {
    .dispatch_events = game_dispatch_events,
    .update = game_update,
    .count_team_members = count_team_members,
    .update_players = update_players,
    .spawn_resources = spawn_resources,
    .update_incantations = update_incantations,
    .check_incantate = check_incantate,
};

/**
 * @brief Register game-related events to the dispatcher.
 *
 * @param dispatcher Pointer to the event dispatcher.
 * @param game Pointer to the game instance.
 */
static void register_event_game(dispatcher_t *dispatcher, game_t *game)
{
    REGISTER(dispatcher, "PLAYER_MOVED", on_player_moved, game);
    REGISTER(dispatcher, "PLAYER_DIED", on_player_died, game);
    REGISTER(dispatcher, "CONNECT_NBR", on_connect_nbr, game);
    REGISTER(dispatcher, "LOOK_AROUND", on_look, game);
}

/****************************************************************************/
/*                                                                          */
/*                         MAP INITIALIZATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Initialize a tile's coordinates and clear its resources.
 *
 * @param tile Pointer to the tile to initialize.
 * @param x X coordinate.
 * @param y Y coordinate.
 */
static void game_init_tile(tile_t *tile, int x, int y)
{
    tile->x = x;
    tile->y = y;
    for (int r = 0; r < RESOURCE_COUNT; r++)
        tile->resources[r] = 0;
}

/**
 * @brief Spawn an egg for a team at a random map position.
 *
 * @param node List node containing the team name.
 * @param egg_id Pointer to the egg ID counter to increment.
 * @param game Pointer to the game instance.
 */
static void init_egg(list_node_t *node, int *egg_id, game_t *game)
{
    egg_t *egg;

    egg = malloc(sizeof(egg_t));
    if (!egg)
        return;
    egg->id = *egg_id;
    *egg_id += 1;
    egg->player_id = -1;
    egg->team_name = (const char *)node->data;
    egg->x = rand() % game->width;
    egg->y = rand() % game->height;
    list_push_back(game->eggs, egg);
    console_log(LOG_INFO, "Egg %d spawned for team '%s' at (%d, %d)",
        egg->id, egg->team_name, egg->x, egg->y);
}

/**
 * @brief Initialize all team eggs on the map.
 *
 * Spawns one egg per team slot available.
 *
 * @param game Pointer to the game instance.
 */
static void game_init_eggs(game_t *game)
{
    int egg_id = 1;
    list_node_t *node = NULL;

    if (!game || !game->team_name)
        return;
    for (node = game->team_name->head; node; node = node->next) {
        for (int i = 0; i < game->team_size; i++) {
            init_egg(node, &egg_id, game);
        }
    }
}

/**
 * @brief Initialize the game map, tiles, resources and eggs.
 *
 * @param game Pointer to the game instance.
 * @return true on success, false if memory allocation fails.
 */
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
    game->methods->spawn_resources(game);
    game_init_eggs(game);
    return true;
}

/****************************************************************************/
/*                                                                          */
/*                        LIST INITIALIZATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Initializes the internal lists used in the game.
 *
 * Creates and assigns the player list, egg list, incantation list,
 * and event queue. Each list uses a dedicated free function if needed.
 *
 * @param game Pointer to the game instance.
 * @return true if all lists were successfully created, false otherwise.
 */
static bool game_init_lists(game_t *game)
{
    game->players = NEW(list, NULL);
    game->eggs = NEW(list, free);
    game->incantations = NEW(list, NULL);
    game->event_queue = NEW(list, free);
    game->server_event_queue = NEW(list, free);
    return game->players && game->eggs && game->event_queue &&
    game->incantations;
}

/****************************************************************************/
/*                                                                          */
/*                             CONSTRUCTOR                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Creates and initializes a new game instance.
 *
 * Allocates and configures a new `game_t` structure based on the given
 * configuration. Initializes the map, internal lists, and event dispatcher.
 *
 * @param config Pointer to the game configuration structure.
 * @return Pointer to the initialized game, or NULL on failure.
 */
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
    register_event_game(game->dispatcher, game);
    if (!game->dispatcher)
        return NULL;
    if (!game_init_lists(game) || !game_init_map(game))
        return NULL;
    return game;
}
