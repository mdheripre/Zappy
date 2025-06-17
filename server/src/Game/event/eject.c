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
 * @brief Eject players from the same tile in a specific direction.
 *
 * Updates their positions and stores them in the ejected list.
 *
 * @param game Pointer to the game instance.
 * @param source Pointer to the player performing the ejection.
 * @param ejected List to store ejected players.
 */
static void eject_players(game_t *game, player_t *source, list_t *ejected)
{
    player_t *target = NULL;
    int dx = 0;
    int dy = 0;

    get_eject_direction(source->orientation, &dx, &dy);
    for (list_node_t *node = game->players->head; node; node = node->next) {
        target = node->data;
        if (!target || target == source)
            continue;
        if (target->x == source->x && target->y == source->y) {
            target->x = (target->x + dx + game->width) % game->width;
            target->y = (target->y + dy + game->height) % game->height;
            list_push_back(ejected, target);
        }
    }
}

/**
 * @brief Send a game event to notify that an egg has died.
 *
 * @param game Pointer to the game instance.
 * @param egg Pointer to the egg that died.
 */
static void send_egg_death_event(game_t *game, egg_t *egg)
{
    game_event_t *egg_death = malloc(sizeof(game_event_t));

    if (!egg_death)
        return;
    egg_death->type = GAME_EVENT_RESPONSE_EGG_DIE;
    egg_death->data.egg.player_id = egg->id;
    egg_death->data.egg.x = egg->x;
    egg_death->data.egg.y = egg->y;
    egg_death->data.egg.team_name = egg->team_name;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, egg_death);
}

/**
 * @brief Check and handle eggs on the same tile as the player.
 *
 * Triggers death events for any eggs present on the tile.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player that caused the check.
 */
static void handle_egg_death(game_t *game, player_t *player)
{
    egg_t *egg = NULL;

    for (list_node_t *node = game->eggs->head; node; node = node->next) {
        egg = node->data;
        if (!egg)
            continue;
        if (egg->x == player->x && egg->y == player->y)
            send_egg_death_event(game, egg);
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
 * @brief Send an "eject: K" message to an ejected player.
 *
 * @param game Pointer to the game instance.
 * @param source Pointer to the ejecting player.
 * @param target Pointer to the ejected player.
 */
static void send_ejected_message(game_t *game, player_t *source,
    player_t *target)
{
    game_event_t *event = malloc(sizeof(game_event_t));
    char buf[BUFFER_SIZE];
    int k = 0;

    if (!event || !source || !target)
        return;
    event->type = GAME_EVENT_RESPONSE_PLAYER_EJECTED;
    event->data.generic_response.client_fd = -1;
    event->data.generic_response.player_id = target->id;
    k = get_eject_message_k(source->orientation);
    snprintf(buf, sizeof(buf), "eject: %d\n", k);
    event->data.generic_response.response = strdup(buf);
    if (!event->data.generic_response.response) {
        free(event);
        return;
    }
    game->server_event_queue->methods->push_back(
        game->server_event_queue, event);
}

/**
 * @brief Send the ejection result to the owner and notify ejected players.
 *
 * @param game Pointer to the game instance.
 * @param event Original ejection event.
 * @param player Pointer to the ejecting player.
 * @param ejected List of players who were ejected.
 */
static void handle_eject_response(game_t *game, game_event_t *event,
    player_t *player, list_t *ejected)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return;
    response->type = GAME_EVENT_RESPONSE_PLAYER_OWNER_EJECTED;
    response->data.generic_response.client_fd =
        event->data.generic_response.client_fd;
    response->data.generic_response.player_id = player->id;
    response->data.generic_response.response = strdup(
        ejected->size > 0 ? "ok\n" : "ko\n");
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
    for (list_node_t *n = ejected->head; n; n = n->next)
        send_ejected_message(game, player, n->data);
}

/**
 * @brief Handle the ejection of players from a tile.
 *
 * Applies the ejection, sends response events, and handles egg destruction.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the ejection game event.
 */
void on_eject(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *player = find_player_by_id(game,
        event->data.generic_response.player_id);
    list_t *ejected = NEW(list, NULL);

    if (!game || !event || !player || !ejected)
        return;
    eject_players(game, player, ejected);
    handle_eject_response(game, event, player, ejected);
    handle_egg_death(game, player);
}
