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
 * @brief Retrieves the client associated with a given player.
 *
 * @param server Pointer to the server structure.
 * @param player Pointer to the player to search for.
 * @param index Optional pointer to store the found client's
 *              index (can be NULL).
 * @return Pointer to the matching client_t, or NULL if not found or on error.
 */
client_t *get_client_by_player(server_t *server, player_t *player,
    int *index)
{
    if (!server || !player)
        return NULL;
    for (int i = 0; i < server->client_count; ++i) {
        if (server->clients[i].player == player) {
            if (index)
                *index = i;
            return &server->clients[i];
        }
    }
    return NULL;
}
