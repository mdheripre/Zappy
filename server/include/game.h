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
typedef struct incantation_s incantation_t;
typedef struct client_s client_t;
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

typedef enum move_direction_e {
    MOVE_FORWARD,
    TURN_LEFT,
    TURN_RIGHT
} move_direction_t;

typedef struct {
    event_type_t type;
    union {
        struct {
            player_t *player;
            int x;
            int y;
            move_direction_t direction;
            int orientation;
            bool ia_success;
        } player_moved;
        struct {
            player_t *player;
        } player_died;
        struct {
            player_t *player;
            int x;
            int y;
            const char *team_name;
            int egg_id;
        } egg;
        struct {
            int x;
            int y;
        } tile;
        struct {
            int x;
            int y;
            bool success;
            list_t *participants;
        } incantation;
        struct {
            client_t *client;
            const char *response;
        } generic_response;
        struct {
            player_t *player;
            int type_item;
            bool success;
        } player_item;
    } data;
} game_event_t;

struct game_methods_s {
    void (*dispatch_events)(game_t *self);
    void (*update)(game_t *self, int tick);
    int (*count_team_members)(game_t *self, const char *team_name);
    void (*update_players)(game_t *self, int tick);
    void (*spawn_resources)(game_t *self);
    void (*update_incantations)(game_t *self, int tick);
    bool (*check_incantate)(game_t *self, incantation_t *inc);
    list_t *(*get_players_on_tile)(game_t *self, int x, int y, int level);
    bool (*has_finished)(game_t *self);
    char *(*get_winner)(game_t *self);
};

typedef struct egg_s {
    int id;
    player_t *player;
    int x;
    int y;
    const char *team_name;
} egg_t;

typedef struct incantation_rule_s {
    int players;
    int resources[RESOURCE_COUNT];
} incantation_rule_t;

struct incantation_s {
    int x;
    int y;
    int target_level;
    list_t *participants;
    int tick_remaining;
};

typedef struct team_info_s {
    char *team_name;
    int team_size;
    int max_level_players;
} team_info_t;

struct game_s {
    int width;
    int height;
    double frequency;
    unsigned long last_tick_time;
    int tick_counter_tiled;
    unsigned long tick_counter;
    bool has_finished;
    int max_players;

    tile_t **map;
    list_t *teams;
    list_t *players;
    list_t *eggs;
    list_t *incantations;
    list_t *event_queue;
    list_t *server_event_queue;
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
void game_dispatch_events(game_t *self);
void game_update(game_t *self, int tick);
int count_team_members(game_t *self, const char *team_name);
void update_players(game_t *self, int tick);
void spawn_resources(game_t *self);
void update_incantations(game_t *self, int tick);
bool check_incantate(game_t *game, incantation_t *inc);
list_t *get_players_on_tile(game_t *game, int x, int y, int level);
void emit_tile_update(game_t *game, int x, int y);
int resource_from_string(const char *name);
bool has_finished(game_t *self);
char *get_winner(game_t *self);


/* Event */
void on_player_moved(void *ctx, void *data);
void on_connect_nbr(void *ctx, void *data);
void on_player_died(void *ctx, void *data);
void on_look(void *ctx, void *data);
void on_inventory(void *ctx, void *data);
void on_eject(void *ctx, void *data);
void on_egg_laid(void *ctx, void *data);
void on_end_incantation(void *ctx, void *data);
void on_start_incantation(void *ctx, void *data);
void on_broadcast(void *ctx, void *data);
void on_drop(void *ctx, void *data);
void on_take(void *ctx, void *data);
#endif /* !GAME_H_ */
