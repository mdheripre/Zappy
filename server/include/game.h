/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "list.h"
    #include <stdbool.h>
    #include <stdlib.h>
    #include "dispatcher.h"
    #define RESOURCE_COUNT 7

typedef struct game_s game_t;
typedef struct game_methods_s game_methods_t;
typedef enum resource_type_e resource_type_t;
typedef struct tile_s tile_t;
typedef enum game_event_type_e game_event_type_t;
typedef struct server_s server_t;
typedef struct player_s player_t;
typedef struct config_game_s config_game_t;

enum resource_type_e {
    RESOURCE_FOOD = 0,
    RESOURCE_LINEMATE,
    RESOURCE_DERAUMERE,
    RESOURCE_SIBUR,
    RESOURCE_MENDIANE,
    RESOURCE_PHIRAS,
    RESOURCE_THYSTAME
};

struct tile_s {
    int x;
    int y;
    int resources[RESOURCE_COUNT];
};

enum game_event_type_e {
    GAME_EVENT_PLAYER_MOVED,
    GAME_EVENT_PLAYER_DIED,
    GAME_EVENT_TILE_UPDATED,
    GAME_EVENT_PLAYER_LEVEL_UP,
    GAME_EVENT_EGG_LAID,
    GAME_EVENT_INCANTATION_STARTED,
    GAME_EVENT_INCANTATION_ENDED
};

typedef struct {
    game_event_type_t type;
    union {
        struct {
            int player_id;
            int x;
            int y;
            int orientation;
        } moved;
        struct {
            int player_id;
        } died;
        struct {
            int x;
            int y;
        } tile;
        struct {
            int player_id;
            int new_level;
        } level_up;
        struct {
            int egg_id;
            int player_id;
            int x;
            int y;
        } egg_laid;
    } data;
} game_event_t;

typedef struct {
    game_event_type_t type;
    const char *name;
} event_type_entry_t;

static const event_type_entry_t EVENT_TYPE_MAP[] = {
    { GAME_EVENT_PLAYER_MOVED, "PLAYER_MOVED" },
    { GAME_EVENT_PLAYER_DIED, "PLAYER_DIED" },
    { GAME_EVENT_TILE_UPDATED, "TILE_UPDATED" },
    { GAME_EVENT_PLAYER_LEVEL_UP, "PLAYER_LEVEL_UP" },
    { GAME_EVENT_EGG_LAID, "EGG_LAID" },
    { GAME_EVENT_INCANTATION_STARTED, "INCANTATION_STARTED" },
    { GAME_EVENT_INCANTATION_ENDED, "INCANTATION_ENDED" },
};

struct game_methods_s {
    void (*tick)(game_t *self, long current_time);
    void (*add_event)(game_t *self, game_event_t event);
    game_event_t *(*pop_event)(game_t *self);
    void (*dispatch_events)(game_t *self);
    void (*update)(game_t *self);
    int (*count_team_members)(game_t *self, const char *team_name);
};

typedef struct egg_s {
    int id;
    int player_id;
    int x;
    int y;
    long hatch_time;
} egg_t;

typedef struct incantation_s {
    int x;
    int y;
    int target_level;
    list_t *participants;
    long end_time;
    bool started;
} incantation_t;

struct game_s {
    int width;
    int height;
    double frequency;
    long last_tick_time;
    bool started;
    int team_size;

    tile_t **map;
    list_t *team_name;
    list_t *players;
    list_t *eggs;
    list_t *incantations;
    list_t *event_queue;
    dispatcher_t *dispatcher;
    const game_methods_t *methods;
};

struct config_game_s {
    int width;
    int height;
    double frequency;
    int team_size;
    list_t *team_name;
};

game_t *game_create(config_game_t *config);
void game_destroy(game_t *game);
void game_tick(game_t *self, long current_time);
void game_add_event(game_t *self, game_event_t event);
game_event_t *game_pop_event(game_t *self);
void game_dispatch_events(game_t *self);
void game_update(game_t *self);
int count_team_members(game_t *self, const char *team_name);
#endif /* !GAME_H_ */
