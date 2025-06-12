/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_gui_client
*/

#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Get the GUI client from the server.
 *
 * This function iterates through the server's clients and returns the first
 * client that is of type CLIENT_GUI and is connected.
 *
 * @param server Pointer to the server instance.
 * @return Pointer to the GUI client, or NULL if no such client exists.
 */
client_t *get_gui_client(server_t *server)
{
    client_t *client = NULL;

    if (!server)
        return NULL;
    for (int i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (client && client->type == CLIENT_GUI && client->connected)
            return client;
    }
    return NULL;
}
