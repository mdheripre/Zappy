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

void on_response_end_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *p = NULL;
    int fd = -1;

    if (!server || !event)
        return;
    for (list_node_t *n = event->data.incantation.participants->head; n;
            n = n->next) {
        p = n->data;
        if (!p)
            continue;
        fd = get_client_fd_by_player(server, p, NULL);
        if (fd != -1)
            dprintf(fd, event->data.incantation.success
                ? "elevation underway\n" : "ko\n");
    }
}
