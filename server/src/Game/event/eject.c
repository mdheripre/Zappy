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

void on_eject(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    game_event_t *response = malloc(sizeof(game_event_t));
    player_t *player = find_player_by_id(game,
        event->data.generic_response.player_id);
    list_t *ejected = NEW(list, NULL);

    if (!game || !event || !player || !ejected)
        return;
    eject_players(game, player, ejected);
    response->type = GAME_EVENT_RESPONSE_PLAYER_EJECTED;
    response->data.generic_response.client_fd =
        event->data.generic_response.client_fd;
    response->data.generic_response.player_id =
        player->id;
    response->data.generic_response.response = strdup(ejected->size > 0 ?
        "ok\n" : "ko\n");
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}
