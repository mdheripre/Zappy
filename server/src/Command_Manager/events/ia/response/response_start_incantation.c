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
 * @brief Send a "ko" response to the first player in the list.
 *
 * Used when an incantation start fails.
 *
 * @param server Pointer to the server instance.
 * @param participants List of participants.
 */
static void send_ko_to_first_participant(server_t *server,
    list_t *participants)
{
    player_t *player = NULL;
    int fd = -1;

    if (participants && participants->head) {
        player = participants->head->data;
        fd = get_client_fd_by_player(server, player, NULL);
        if (fd != -1)
            dprintf(fd, "ko\n");
    }
}

/**
 * @brief Notify all incantation participants of a successful ritual.
 *
 * Sends "elevation underway" and marks each player as stuck.
 *
 * @param server Pointer to the server instance.
 * @param participants List of players in the incantation.
 */
static void notify_participants_elevation(server_t *server,
    list_t *participants)
{
    player_t *player = NULL;
    client_t *client = NULL;
    int fd = -1;

    for (list_node_t *n = participants->head; n; n = n->next) {
        player = n->data;
        client = get_client_by_player(server, player, NULL);
        if (!client)
            continue;
        client->stuck = true;
        fd = get_client_fd_by_player(server, player, NULL);
        if (fd != -1)
            dprintf(fd, "elevation underway\n");
    }
}

/**
 * @brief Handle the response for the start of an incantation.
 *
 * Notifies participants or sends "ko" if the incantation fails.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the incantation start event.
 */
void on_response_start_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    list_t *participants = event->data.incantation.participants;

    if (!server || !event)
        return;
    if (!event->data.incantation.success) {
        send_ko_to_first_participant(server, participants);
        return;
    }
    notify_participants_elevation(server, participants);
}
