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
 * @brief Send an incantation result response to a player.
 *
 * Unstucks the player, sends the appropriate message, and updates
 * the next command's tick tracking if needed.
 *
 * @param server Pointer to the server instance.
 * @param event Pointer to the incantation game event.
 * @param player Pointer to the player receiving the result.
 */
static void send_incantation_response(server_t *server, game_event_t *event,
    player_t *player)
{
    client_t *client = get_client_by_player(server, player, NULL);
    queued_command_t *next = NULL;
    int fd = -1;

    if (!player || !client)
        return;
    client->stuck = false;
    fd = get_client_fd_by_player(server, player, NULL);
    if (fd != -1)
        dprintf(fd, event->data.incantation.success
            ? "elevation underway\n" : "ko\n");
    next = client_peek_command(client);
    if (next && next->ticks_remaining > 0)
        next->last_tick_checked = server->game->tick_counter + 1;
}

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
    player_t *player = NULL;

    if (!server || !event)
        return;
    for (list_node_t *n = event->data.incantation.participants->head; n;
            n = n->next) {
        player = n->data;
        send_incantation_response(server, event, player);
    }
}
