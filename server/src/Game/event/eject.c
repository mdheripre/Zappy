/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** eject
*/

#include "game.h"
#include "utils.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Get the direction vector based on player's orientation.
 *
 * @param orientation Orientation of the player.
 * @param dx Output X direction.
 * @param dy Output Y direction.
 */
static void get_eject_direction(player_orientation_t orientation,
    int *dx, int *dy)
{
    *dx = 0;
    *dy = 0;
    switch (orientation) {
        case ORIENTATION_NORTH:
            *dy = -1;
            break;
        case ORIENTATION_EAST:
            *dx = 1;
            break;
        case ORIENTATION_SOUTH:
            *dy = 1;
            break;
        case ORIENTATION_WEST:
            *dx = -1;
            break;
    }
}

/**
 * @brief Get the direction code (K) for an ejection message.
 *
 * @param orientation Orientation of the ejecting player.
 * @return Direction code from 1 to 8, or 0 if invalid.
 */
static int get_eject_message_k(player_orientation_t orientation)
{
    switch (orientation) {
        case ORIENTATION_NORTH:
            return 1;
        case ORIENTATION_EAST:
            return 3;
        case ORIENTATION_SOUTH:
            return 5;
        case ORIENTATION_WEST:
            return 7;
        default:
            return 0;
    }
}

/**
 * Moves players on the same tile as the source in the direction of ejection.
 *
 * Computes the direction from the source orientation and moves all other
 * players on the same tile accordingly. Adds ejected players to the
 * provided list.
 *
 * @param game Pointer to the game structure.
 * @param src The player initiating the ejection.
 * @param ejected List where ejected players will be stored.
 */
static void eject_players(game_t *game, player_t *src, list_t *ejected)
{
    int dx;
    int dy;
    player_t *p;

    get_eject_direction(src->orientation, &dx, &dy);
    for (list_node_t *node = game->players->head; node; node = node->next) {
        p = node->data;
        if (!p || p == src)
            continue;
        if (p->x == src->x && p->y == src->y) {
            p->x = (p->x + dx + game->width) % game->width;
            p->y = (p->y + dy + game->height) % game->height;
            list_push_back(ejected, p);
        }
    }
}

/**
 * Sends an eject notification to the target player.
 *
 * Builds a message with the correct 'k' value depending on the direction
 * and sends it as an event to the target's client.
 *
 * @param game Pointer to the game structure.
 * @param src The player who initiated the ejection.
 * @param tgt The target player who was ejected.
 */
static void send_ejected_msg(game_t *game, player_t *src, player_t *tgt)
{
    int k = get_eject_message_k(src->orientation);
    char msg[BUFFER_SIZE];
    game_event_t *ev = NULL;

    snprintf(msg, sizeof(msg), "eject: %d\n", k);
    ev = calloc(1, sizeof(game_event_t));
    if (!ev)
        return;
    ev->type = EVENT_RESP_PLAYER_EJECTED;
    ev->data.generic_response.client = tgt->client;
    ev->data.generic_response.response = strdup(msg);
    if (!ev->data.generic_response.response)
        return free(ev);
    game->server_event_queue->methods->push_back(game->server_event_queue, ev);
}

/**
 * Emits an egg death event and removes it from the list.
 *
 * Notifies the GUI that an egg has died at the specified position and
 * removes it from the game’s egg list.
 *
 * @param game Pointer to the game structure.
 * @param egg Pointer to the egg being destroyed.
 * @param node The list node corresponding to the egg.
 */
static void send_egg_death(game_t *game, egg_t *egg, list_node_t *node)
{
    game_event_t *ev = calloc(1, sizeof(game_event_t));

    if (!ev)
        return;
    ev->type = EVENT_RESP_EGG_DIE;
    ev->data.egg.egg_id = egg->id;
    ev->data.egg.x = egg->x;
    ev->data.egg.y = egg->y;
    ev->data.egg.team_name = egg->team_name;
    game->server_event_queue->methods->push_back(game->server_event_queue, ev);
    game->eggs->methods->remove(game->eggs, node->data);
}

/**
 * Destroys all eggs at the same position as the player.
 *
 * Iterates over all eggs and removes those located on the player's tile.
 *
 * @param game Pointer to the game structure.
 * @param p The player used to identify egg position.
 */
static void destroy_eggs_at_pos(game_t *game, player_t *p)
{
    list_node_t *node = game->eggs->head;
    list_node_t *next = NULL;
    egg_t *egg = NULL;

    while (node) {
        next = node->next;
        egg = node->data;
        if (egg && egg->x == p->x && egg->y == p->y)
            send_egg_death(game, egg, node);
        node = next;
    }
}

/**
 * Sends the eject response to the source player and ejected targets.
 *
 * Sends a response to the source indicating success or failure, then
 * notifies each ejected player of their new direction.
 *
 * @param game Pointer to the game structure.
 * @param src The player who initiated the ejection.
 * @param ejected List of players who were ejected.
 */
static void send_eject_response(game_t *game,
    player_t *src, list_t *ejected)
{
    game_event_t *ev = calloc(1, sizeof(game_event_t));

    if (!ev)
        return;
    ev->type = EVENT_RESP_PLAYER_OWNER_EJECTED;
    ev->data.generic_response.client = src->client;
    ev->data.generic_response.response = strdup(
        ejected->size > 0 ? "ok\n" : "ko\n");
    game->server_event_queue->methods->push_back(game->server_event_queue, ev);
    for (list_node_t *n = ejected->head; n; n = n->next)
        send_ejected_msg(game, src, n->data);
}

/**
 * Handles the eject action triggered by a player.
 *
 * Processes the ejection: updates positions, removes eggs if needed, and
 * emits appropriate responses for GUI and players.
 *
 * @param ctx Pointer to the game instance (game_t *).
 * @param data Pointer to the event (game_event_t *).
 */
void on_eject(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *player = event->data.generic_response.client->player;
    list_t *ejected = NEW(list, NULL);

    if (!game || !event || !player || !ejected)
        return;
    eject_players(game, player, ejected);
    destroy_eggs_at_pos(game, player);
    send_eject_response(game, player, ejected);
}
