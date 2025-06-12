/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_client_index_by_player
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Retrieves the index of a client associated with a player.
 *
 * @param server Pointer to the server structure.
 * @param player Pointer to the player to search for.
 * @return Index of the client, or -1 if not found or on error.
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
