/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_client_by_player
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

client_t *get_client_by_player(server_t *server, player_t *player)
{
    list_node_t *node = NULL;
    client_t *client = NULL;

    if (!server || !player || !server->clients)
        return NULL;
    for (node = server->clients->head; node; node = node->next) {
        client = node->data;
        if (client && client->player == player)
            return client;
    }
    return NULL;
}
