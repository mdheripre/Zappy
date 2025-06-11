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

static void send_ko_to_participants(server_t *server,
    incantation_t *incantation)
{
    player_t *p = NULL;
    int fd = -1;

    if (!incantation || !incantation->participants)
        return;
    for (list_node_t *n = incantation->participants->head; n; n = n->next) {
        p = n->data;
        if (!p)
            continue;
        fd = get_client_fd_by_player(server, p, NULL);
        if (fd != -1)
            dprintf(fd, "ko\n");
    }
}

void on_response_start_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;

    if (!server || !event)
        return;
    if (!event->data.incantation.success) {
        send_ko_to_participants(server, &event->data.incantation);
        return;
    }
}
