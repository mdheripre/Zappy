/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_start_incantation
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

static void send_ko_to_first_participant(list_t *participants)
{
    player_t *player = NULL;
    client_t *client = NULL;

    if (!participants || !participants->head)
        return;
    player = participants->head->data;
    client = player->client;
    if (client)
        dprintf(client->fd, "ko\n");
}

static void notify_participants_elevation(list_t *participants)
{
    player_t *player = NULL;
    client_t *client = NULL;

    for (list_node_t *n = participants->head; n; n = n->next) {
        player = n->data;
        client = player->client;
        if (!client)
            continue;
        client->stuck = true;
        dprintf(client->fd, "elevation underway\n");
    }
}

void on_response_start_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    list_t *participants = event->data.incantation.participants;

    if (!server || !event)
        return;
    if (!event->data.incantation.success) {
        send_ko_to_first_participant(participants);
        return;
    }
    notify_participants_elevation(participants);
    EMIT(server->command_manager->dispatcher, EVENT_GUI_PIC, event);
}
