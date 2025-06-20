/*
** EPITECH PROJECT, 2025
** server
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #define INVENTORY_SIZE 7


typedef struct player_s player_t;
typedef struct client_s client_t;
typedef struct game_s game_t;
typedef enum move_direction_e move_direction_t;

typedef enum player_orientation_e {
    ORIENTATION_NORTH = 1,
    ORIENTATION_EAST,
    ORIENTATION_SOUTH,
    ORIENTATION_WEST
} player_orientation_t;

typedef struct {
    int id;
    int x;
    int y;
    player_orientation_t orientation;
    const char *team_name;
} player_config_t;


typedef struct player_methods_s {
    void (*move)(player_t *self, int map_width, int map_height,
        move_direction_t dir);
    void (*die)(player_t *self);
    void (*add_resource)(player_t *self, int resource_type, int amount);
    void (*remove_resource)(player_t *self, int resource_type, int amount);
    void (*update)(player_t *self, game_t *game, int ticks);
} player_methods_t;

struct player_s {
    int id;
    int x;
    int y;
    player_orientation_t orientation;
    int level;
    bool is_alive;
    char *team_name;
    int inventory[INVENTORY_SIZE];
    int nbr_tick;

    const player_methods_t *methods;
};

player_t *player_create(player_config_t config);
void player_destroy(player_t *self);
void player_update(player_t *self, game_t *game, int ticks);
void player_die(player_t *self);
void player_move(player_t *self, int map_width, int map_height,
    move_direction_t dir);
void player_add_resource(player_t *self, int type, int amount);
void player_remove_resource(player_t *self, int type, int amount);
#endif /* !PLAYER_H_ */
