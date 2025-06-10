/*
** EPITECH PROJECT, 2025
** server
** File description:
** look_around
*/

#include "game.h"
#include "player.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief String names for each resource type, indexed by enum.
 */
static const char *RESOURCE_NAMES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

/**
 * @brief Append a resource name to the buffer with spacing.
 *
 * @param buf Output buffer.
 * @param size Size of the buffer.
 * @param name Resource name to append.
 * @param first Flag to manage spacing.
 */
static void append_single_resource(char *buf, size_t size,
    const char *name, bool *first)
{
    if (!*first)
        strncat(buf, " ", size - strlen(buf) - 1);
    strncat(buf, name, size - strlen(buf) - 1);
    *first = false;
}

/**
 * @brief Append all resources from a tile into a buffer.
 *
 * @param tile Tile containing resources.
 * @param buf Output buffer.
 * @param size Size of the buffer.
 */
static void append_resource_names(tile_t *tile, char *buf, size_t size)
{
    bool first = true;

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        for (int j = 0; j < tile->resources[i]; j++) {
            append_single_resource(buf, size, RESOURCE_NAMES[i], &first);
        }
    }
}

/**
 * @brief Wrap coordinates around the map using toroidal logic.
 *
 * @param game Pointer to the game instance.
 * @param x Raw X coordinate.
 * @param y Raw Y coordinate.
 * @return Wrapped coordinates as a vector2i_t.
 */
static vector2i_t get_torus_coords(game_t *game, int x, int y)
{
    vector2i_t pos;

    pos.x = (x + game->width) % game->width;
    pos.y = (y + game->height) % game->height;
    return pos;
}

/**
 * @brief Append resource names from a tile relative to the player.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player.
 * @param query Relative offset and output buffer.
 */
static void get_tile_at(game_t *game, player_t *player,
    query_t query)
{
    vector2i_t pos = get_torus_coords(game, player->x + query.dx,
        player->y + query.dy);
    tile_t *tile = &game->map[pos.y][pos.x];

    append_resource_names(tile, query.buffer, BUFSIZ);
}

/**
 * @brief Compute tile offset for a given vision layer and orientation.
 *
 * @param orientation Player's orientation.
 * @param d Distance from the player.
 * @param i Horizontal offset within the layer.
 * @param offset Output offset vector.
 */
static void get_layer_offsets(int orientation, int d, int i,
    vector2i_t *offset)
{
    switch (orientation) {
        case ORIENTATION_NORTH:
            offset->x = i;
            offset->y = -d;
            break;
        case ORIENTATION_EAST:
            offset->x = d;
            offset->y = i;
            break;
        case ORIENTATION_SOUTH:
            offset->x = -i;
            offset->y = d;
            break;
        case ORIENTATION_WEST:
            offset->x = -d;
            offset->y = -i;
            break;
    }
}

/**
 * @brief Explore and append all tiles in a vision layer.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player.
 * @param d Vision layer depth.
 * @param buffer Output buffer.
 */
static void explore_layer(game_t *game, player_t *player, int d, char *buffer)
{
    query_t query;
    vector2i_t offset;

    for (int i = -d; i <= d; i++) {
        get_layer_offsets(player->orientation, d, i, &offset);
        if (d != 0 || i != (d * -1))
            strncat(buffer, ",", BUFSIZ - strlen(buffer) - 1);
        query.dx = offset.x;
        query.dy = offset.y;
        query.buffer = buffer;
        get_tile_at(game, player, query);
    }
}

/**
 * @brief Build the full response for the 'Look' command.
 *
 * @param g Pointer to the game instance.
 * @param p Pointer to the player.
 * @param buf Output buffer.
 */
static void build_look_response(game_t *g, player_t *p, char *buf)
{
    strncat(buf, "[", BUFSIZ - 1);
    for (int d = 0; d <= p->level; d++)
        explore_layer(g, p, d, buf);
    strncat(buf, "]\n", BUFSIZ - strlen(buf) - 1);
}

/**
 * @brief Handle a look event and generate a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the look event.
 */
void on_look(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *p = find_player_by_id(game,
        event->data.generic_response.player_id);
    game_event_t *resp = malloc(sizeof(game_event_t));
    char *buffer = calloc(BUFSIZ, sizeof(char));

    if (!game || !event || !p || !resp || !buffer)
        return;
    build_look_response(game, p, buffer);
    resp->type = GAME_EVENT_RESPONSE_LOOK;
    resp->data.generic_response.client_fd = event->
    data.generic_response.client_fd;
    resp->data.generic_response.response = buffer;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        resp);
}
