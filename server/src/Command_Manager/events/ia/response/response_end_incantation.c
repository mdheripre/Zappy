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

/**
 * @brief Handle the response to an incantation ending.
 *
 * Sends "elevation underway" or "ko" to each participating player.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the incantation event.
 */
void on_response_end_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *p = NULL;
    client_t *client = NULL;
    int fd = -1;

    if (!server || !event)
        return;
    for (list_node_t *n = event->data.incantation.participants->head; n;
            n = n->next) {
        p = n->data;
        client = get_client_by_player(server, p, NULL);
        if (!p || !client)
            continue;
        client->stuck = false;
        fd = get_client_fd_by_player(server, p, NULL);
        if (fd != -1)
            dprintf(fd, event->data.incantation.success
                ? "elevation underway\n" : "ko\n");
    }
}
