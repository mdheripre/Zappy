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

/**
 * @brief Send a "ko" message to all incantation participants.
 *
 * @param server Pointer to the server.
 * @param participants List of participating players.
 */
static void send_ko_to_participants(server_t *server,
    list_t *participants)
{
    player_t *p = NULL;
    int fd = -1;

    if (!participants)
        return;
    for (list_node_t *n = participants->head; n; n = n->next) {
        p = n->data;
        if (!p)
            continue;
        fd = get_client_fd_by_player(server, p, NULL);
        if (fd != -1)
            dprintf(fd, "ko\n");
    }
}

/**
 * @brief Handle the start of an incantation response.
 *
 * Sends "ko" to participants if the incantation failed.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the incantation event.
 */
void on_response_start_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event)
        return;
    if (!event->data.incantation.success) {
        send_ko_to_participants(server, event->data.incantation.participants);
        return;
    }
    for (list_node_t *n = event->data.incantation.participants->head;
            n; n = n->next) {
        client = get_client_by_player(server, n->data, NULL);
        if (!client)
            continue;
        client->stuck = true;
    }
}
