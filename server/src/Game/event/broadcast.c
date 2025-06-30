 
/*
** EPITECH PROJECT, 2025
** server
** File description:
** broadcast
*/
#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"
#include <math.h>
/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/
/**
 * @brief Compute toroidal vector from sender to receiver.
 *
 * Wraps the coordinates to respect map edges.
 *
 * @param game Pointer to the game instance.
 * @param sender Pointer to the sending player.
 * @param r Pointer to the receiving player.
 * @return Vector from sender to receiver with torus logic.
 */
static vector2i_t compute_direction(game_t *game, player_t *receiver,
    player_t *sender)
{
    vector2i_t v = { sender->x - receiver->x, sender->y - receiver->y };
    if (v.x > game->width / 2)
        v.x -= game->width;
    else if (v.x < (game->width * -1) / 2)
        v.x += game->width;
    if (v.y > game->height / 2)
        v.y -= game->height;
    else if (v.y < (game->height * -1) / 2)
        v.y += game->height;
    return v;
}
/**
 * @brief Get angle offset based on player's orientation.
 *
 * @param orientation Orientation enum value.
 * @return Angle in degrees to adjust the direction.
 */
static float orientation_offset(player_orientation_t orientation)
{
    switch (orientation) {
        case ORIENTATION_NORTH:
            return 90.0f;
        case ORIENTATION_EAST:
            return 0.0f;
        case ORIENTATION_SOUTH:
            return 270.0f;
        case ORIENTATION_WEST:
            return 180.0f;
        default:
            return 0.0f;
    }
}
/**
 * @brief Convert angle to one of the 8 broadcast sectors.
 *
 * @param angle Angle in degrees.
 * @return Sector number (1 to 8).
 */
static int angle_to_sector(float angle)
{
    static const int sector_table[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sector = (int)((angle + 22.5f) / 45.0f);
    sector = sector % 8;
    return sector_table[sector];
}
/**
 * @brief Compute broadcast direction from sender to receiver.
 *
 * Takes into account map wrapping and receiver's orientation.
 *
 * @param game Pointer to the game instance.
 * @param sender Pointer to the sending player.
 * @param r Pointer to the receiving player.
 * @return Direction sector (1 to 8).
 */
int compute_broadcast_direction(game_t *game, player_t *sender,
    player_t *receiver)
{
    vector2i_t dir;
    float angle = 0.0f;
    if (!sender || !receiver || sender == receiver)
        return 0;
    dir = compute_direction(game, receiver, sender);
    if (dir.x == 0 && dir.y == 0)
        return 0;
    angle = atan2f(-dir.y, dir.x) * 180.0f / (float)M_PI;
    if (angle < 0.0f)
        angle += 360.0f;
    if (angle >= 360.0f)
        angle -= 360.0f;
    angle -= orientation_offset(receiver->orientation);
    if (angle < 0.0f)
        angle += 360.0f;
    if (angle >= 360.0f)
        angle -= 360.0f;
    return angle_to_sector(angle);
}
static game_event_t *create_broadcast_event(player_t *player,
    const char *msg, bool to_gui)
{
    game_event_t *event = malloc(sizeof(game_event_t));
    if (!event)
        return NULL;
    memset(event, 0, sizeof(game_event_t));
    event->type = to_gui ? EVENT_RESP_BROADCAST_TO_GUI :
        EVENT_RESP_BROADCAST;
    event->data.generic_response.client = player->client;
    event->data.generic_response.response = strdup(msg);
    return event;
}
/**
 * @brief Send a broadcast message to all players except the sender.
 *
 * Computes the direction for each recipient and queues an event.
 *
 * @param game Pointer to the game instance.
 * @param sender Pointer to the player sending the message.
 * @param msg The message content.
 */
static void broadcast_to_players(game_t *game, player_t *sender,
    const char *msg)
{
    player_t *target = NULL;
    char buf[BUFFER_SIZE] = {0};
    int dir = -1;
    game_event_t *event = NULL;
    for (list_node_t *n = game->players->head; n; n = n->next) {
        target = n->data;
        memset(buf, 0, sizeof(buf));
        if (!target || target == sender)
            continue;
        dir = compute_broadcast_direction(game, sender, target);
        snprintf(buf, sizeof(buf), "message %d, %s\n", dir, msg);
        event = create_broadcast_event(target, buf, false);
        if (event)
            game->server_event_queue->methods->push_back(
                game->server_event_queue, event);
    }
    event = create_broadcast_event(sender, msg, true);
    game->server_event_queue->methods->push_back(
        game->server_event_queue, event);
}
/**
 * @brief Handle the broadcast command from a player.
 *
 * Dispatches messages to all other players and sends "ok" to sender.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the broadcast event.
 */
void on_broadcast(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *sender = event->data.generic_response.client->player;
    const char *msg = event->data.generic_response.response;
    game_event_t *ok = NULL;
    if (!game || !event || !sender || !msg)
        return;
    broadcast_to_players(game, sender, msg);
    ok = create_broadcast_event(sender, "ok\n", false);
    if (ok)
        game->server_event_queue->methods->push_back(game->server_event_queue,
            ok);
    free((char *)msg);
}
