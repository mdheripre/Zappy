/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_end_incantation
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

static void send_incantation_result(server_t *server,
    game_event_t *event, player_t *player)
{
    client_t *client = player->client;

    if (!client)
        return;
    client->stuck = false;
    if (event->data.incantation.success) {
        dprintf(client->fd, "current level: %d\n", player->level);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PLV, &player->id);
    } else {
        dprintf(client->fd, "ko\n");
    }
}

static void replan_next_command(server_t *server, player_t *player)
{
    client_t *client = player->client;
    queued_command_t *next = NULL;

    if (!client)
        return;
    next = client_peek_command(client);
    if (next && next->ticks_remaining > 0)
        next->last_tick_checked = server->game->tick_counter + 1;
}

void on_response_end_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = NULL;

    if (!server || !event)
        return;
    for (list_node_t *n = event->data.incantation.participants->head;
        n; n = n->next) {
        player = n->data;
        send_incantation_result(server, event, player);
        replan_next_command(server, player);
    }
    EMIT(server->command_manager->dispatcher, EVENT_GUI_PIE, event);
}
