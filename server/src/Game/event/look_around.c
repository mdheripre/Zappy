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
 * @brief Append a word to a buffer with spacing logic.
 *
 * @param buf Output buffer.
 * @param name Word to append.
 * @param first Pointer to a flag indicating if this is the first element.
 */
static void append_single(char *buf, const char *name, bool *first)
{
    size_t len = strlen(buf);

    if (!*first)
        strncat(buf, " ", BUFSIZ - len - 1);
    strncat(buf, name, BUFSIZ - strlen(buf) - 1);
    *first = false;
}

/**
 * @brief Append all alive players found on a tile to the response buffer.
 *
 * @param ctx Write context containing the buffer and spacing flag.
 * @param game Pointer to the game instance.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 */
static void append_players(write_ctx_t *ctx, game_t *game, int x, int y)
{
    list_node_t *node = NULL;
    player_t *pl = NULL;

    for (node = game->players->head; node; node = node->next) {
        pl = node->data;
        if (pl->is_alive && pl->x == x && pl->y == y)
            append_single(ctx->buf, "player", ctx->first);
    }
}

/**
 * @brief Append all resources from a tile to the response buffer.
 *
 * @param tile Pointer to the tile.
 * @param ctx Write context containing the buffer and spacing flag.
 */
static void append_resources(tile_t *tile, write_ctx_t *ctx)
{
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        for (int j = 0; j < tile->resources[i]; j++)
            append_single(ctx->buf, RESOURCE_NAMES[i], ctx->first);
    }
}

/**
 * @brief Append both players and resources of a tile to the response buffer.
 *
 * @param game Pointer to the game instance.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param ctx Write context for the buffer.
 */
static void append_tile(game_t *game, int x, int y, write_ctx_t *ctx)
{
    tile_t *tile = &game->map[y][x];

    append_players(ctx, game, x, y);
    append_resources(tile, ctx);
}

/**
 * @brief Apply toroidal wrapping to coordinates on the map.
 *
 * @param game Pointer to the game instance.
 * @param x Raw X coordinate.
 * @param y Raw Y coordinate.
 * @return Wrapped coordinates.
 */
static vector2i_t wrap_coords(game_t *game, int x, int y)
{
    vector2i_t pos;

    pos.x = (x + game->width) % game->width;
    pos.y = (y + game->height) % game->height;
    return pos;
}

/**
 * @brief Compute the relative offset for a given direction and orientation.
 *
 * @param offset Output vector for the offset.
 * @param orientation Player's orientation.
 * @param d Distance from the player.
 * @param i Lateral offset at the given distance.
 */
static void get_offset(vector2i_t *offset, int orientation, int d, int i)
{
    offset->x = 0;
    offset->y = 0;
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
 * @brief Explore and describe a line of tiles at distance d from the player.
 *
 * @param ctx Pointer to the exploration context.
 * @param d Distance from the player.
 */
static void explore_line(explore_ctx_t *ctx, int d)
{
    vector2i_t offset;
    vector2i_t pos;

    for (int i = -d; i <= d; i++) {
        get_offset(&offset, ctx->player->orientation, d, i);
        pos = wrap_coords(ctx->game,
            ctx->player->x + offset.x,
            ctx->player->y + offset.y);
        if (!*ctx->writer.first)
            strncat(ctx->writer.buf, ",", BUFSIZ -
                strlen(ctx->writer.buf) - 1);
        else
            *ctx->writer.first = false;
        append_tile(ctx->game, pos.x, pos.y, &ctx->writer);
    }
}

/**
 * @brief Build the look response string for a player.
 *
 * @param g Pointer to the game instance.
 * @param p Pointer to the player.
 * @param buf Output buffer to store the formatted response.
 */
static void build_look_response(game_t *g, player_t *p, char *buf)
{
    bool first = true;
    explore_ctx_t ctx = {
        .game = g,
        .player = p,
        .writer = { .buf = buf, .first = &first }
    };

    strncat(buf, "[", BUFSIZ - 1);
    for (int d = 0; d <= p->level; d++)
        explore_line(&ctx, d);
    strncat(buf, "]\n", BUFSIZ - strlen(buf) - 1);
}

/**
 * @brief Create a LOOK response event for a player.
 *
 * @param game Pointer to the game instance.
 * @param p Pointer to the player.
 * @param client_fd File descriptor of the client.
 * @return Pointer to the created game event, or NULL on error.
 */
static game_event_t *create_look_response(game_t *game, player_t *p)
{
    game_event_t *resp = malloc(sizeof(game_event_t));
    char *buffer = calloc(BUFSIZ, sizeof(char));

    if (!resp || !buffer)
        return NULL;
    build_look_response(game, p, buffer);
    resp->type = GAME_EVENT_RESPONSE_LOOK;
    resp->data.generic_response.client = p->client;
    resp->data.generic_response.response = buffer;
    return resp;
}

/**
 * @brief Handle a look command and queue a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the look event.
 */
void on_look(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *p = event->data.generic_response.client->player;
    game_event_t *resp = NULL;

    if (!game || !event || !p)
        return;
    resp = create_look_response(game, p);
    if (!resp)
        return;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        resp);
}
