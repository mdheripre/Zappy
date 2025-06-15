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
    .get_players_on_tile = get_players_on_tile,
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
    REGISTER(dispatcher, "CHECK_INVENTORY", on_inventory, game);
    REGISTER(dispatcher, "PLAYER_EJECT", on_eject, game);
    REGISTER(dispatcher, "EGG_LAID", on_egg_laid, game);
    REGISTER(dispatcher, "START_INCANTATION", on_start_incantation, game);
    REGISTER(dispatcher, "END_INCANTATION", on_end_incantation, game);
    REGISTER(dispatcher, "BROADCAST_MESSAGE", on_broadcast, game);
    REGISTER(dispatcher, "PLAYER_DROP_ITEM", on_drop, game);
    REGISTER(dispatcher, "PLAYER_TAKE_ITEM", on_take, game);
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
 * @brief Free memory allocated for a team_info_t structure.
 *
 * @param data Pointer to the team_info_t to free.
 */
static void free_team_info(void *data)
{
    team_info_t *team = data;

    if (!team)
        return;
    free(team->team_name);
    free(team);
}

/**
 * @brief Initialize the teams from configuration into the game state.
 *
 * Allocates and stores team names and sizes into the game.
 *
 * @param game Pointer to the game instance.
 * @param config Pointer to the game configuration.
 * @return true on success, false on allocation failure.
 */
static bool game_init_teams(game_t *game, config_game_t *config)
{
    list_node_t *node = NULL;
    team_info_t *team = NULL;
    char *name = NULL;

    game->teams = NEW(list, free_team_info);
    if (!game->teams || !config->team_name)
        return false;
    for (node = config->team_name->head; node; node = node->next) {
        name = node->data;
        team = malloc(sizeof(team_info_t));
        if (!team)
            return false;
        team->team_name = strdup(name);
        team->team_size = config->team_size;
        list_push_back(game->teams, team);
    }
    return true;
}

/**
 * @brief Create and spawn a new egg for a team at a random map position.
 *
 * @param team_name Name of the team associated with the egg.
 * @param egg_id Pointer to the egg ID counter (auto-incremented).
 * @param game Pointer to the game instance.
 */
static void init_egg(const char *team_name, int *egg_id, game_t *game)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return;
    egg->id = *egg_id;
    *egg_id += 1;
    egg->player_id = -1;
    egg->team_name = team_name;
    egg->x = rand() % game->width;
    egg->y = rand() % game->height;
    list_push_back(game->eggs, egg);
    console_log(LOG_INFO,
        "Egg %d spawned for team '%s' at (%d, %d)",
        egg->id, egg->team_name, egg->x, egg->y);
}

/**
 * @brief Initialize eggs for all teams in the game.
 *
 * One egg per team slot is created and positioned randomly.
 *
 * @param game Pointer to the game instance.
 */
static void game_init_eggs(game_t *game)
{
    int egg_id = 1;
    list_node_t *node = NULL;
    team_info_t *team = NULL;

    if (!game || !game->teams)
        return;
    for (node = game->teams->head; node; node = node->next) {
        team = node->data;
        if (!team)
            continue;
        for (int i = 0; i < team->team_size; i++) {
            init_egg(team->team_name, &egg_id, game);
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
    game->incantations = NEW(list, free);
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
    if (!game_init_teams(game, config))
        return NULL;
    game->tick_counter_tiled = 0;
    game->last_tick_time = 0;
    game->tick_counter = 0;
    game->methods = &GAME_METHODS;
    game->dispatcher = NEW(dispatcher, NULL);
    register_event_game(game->dispatcher, game);
    if (!game->dispatcher)
        return NULL;
    if (!game_init_lists(game) || !game_init_map(game))
        return NULL;
    return game;
}
