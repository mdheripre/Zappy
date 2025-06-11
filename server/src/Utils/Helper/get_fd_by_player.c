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

/**
 * @brief Get the index of a client associated with a player.
 *
 * @param server Pointer to the server.
 * @param player Pointer to the player.
 * @return Client index, or -1 if not found.
 */
int get_client_index_by_player(server_t *server, player_t *player)
{
    if (!server || !player)
        return -1;
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].player == player)
            return i;
    }
    return -1;
}

/**
 * @brief Get the client file descriptor for a given player.
 *
 * @param server Pointer to the server.
 * @param player Pointer to the player.
 * @param index Optional pointer to store the client index.
 * @return File descriptor, or -1 if not found.
 */
int get_client_fd_by_player(server_t *server, player_t *player, int *index)
{
    int idx = get_client_index_by_player(server, player);

    if (idx == -1)
        return -1;
    if (index)
        *index = idx;
    return server->clients[idx].fd;
}
