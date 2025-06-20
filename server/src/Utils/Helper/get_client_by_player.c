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

/**
 * @brief Get the client associated with a given player.
 *
 * @param server Pointer to the server instance.
 * @param player Pointer to the player.
 * @param index Optional pointer to store the client index.
 * @return Pointer to the client, or NULL if not found.
 */
client_t *get_client_by_player(server_t *server, player_t *player, int *index)
{
    int idx = get_client_index_by_player(server, player);

    if (idx == -1)
        return NULL;
    if (index)
        *index = idx;
    return &server->clients[idx];
}
