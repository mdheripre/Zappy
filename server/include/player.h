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

typedef struct {
    int id;
    int x;
    int y;
    int orientation;
    const char *team_name;
} player_config_t;

typedef struct player_methods_s {
    void (*move)(player_t *self, int dx, int dy);
    void (*die)(player_t *self);
    void (*add_resource)(player_t *self, int resource_type, int amount);
    void (*remove_resource)(player_t *self, int resource_type, int amount);
    void (*update)(player_t *self, game_t *game);
} player_methods_t;

struct player_s {
    int id;
    int x;
    int y;
    int orientation;
    int level;
    bool is_alive;
    char *team_name;
    int inventory[INVENTORY_SIZE];
    int nbr_tick;
    client_t *client;

    const player_methods_t *methods;
};

player_t *player_create(player_config_t config);
void player_destroy(player_t *self);
void player_update(player_t *self, game_t *game);
void player_die(player_t *self);
void player_move(player_t *self, int dx, int dy);
void player_add_resource(player_t *self, int type, int amount);
void player_remove_resource(player_t *self, int type, int amount);
#endif /* !PLAYER_H_ */
