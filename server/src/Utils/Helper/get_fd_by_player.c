/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_fd_by_player
*/

#include "game.h"
#include "player.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

int get_client_fd_by_player(server_t *server, player_t *player)
{
    list_node_t *node = NULL;
    client_t *client = NULL;

    if (!server || !player || !server->clients)
        return -1;
    for (node = server->clients->head; node; node = node->next) {
        client = node->data;
        if (client && client->player == player)
            return client->fd;
    }
    return -1;
}
