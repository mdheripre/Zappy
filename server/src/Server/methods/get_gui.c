/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** get_gui.c
*/

/****************************************************************************/
/*                                                                          */
/*                                 GET GUI                                  */
/*                                                                          */
/****************************************************************************/

#include "client.h"
#include "server.h"

/**
 * @brief Retrieves the GUI client from the server.
 *
 * This function searches through the server's client list to find
 * the first connected client of type CLIENT_GUI.
 *
 * @param server Pointer to the server instance.
 * @return Pointer to the GUI client, or NULL if not found.
 */
client_t *server_get_gui(server_t *server)
{
    client_t *client = NULL;

    if (!server || !server->clients)
        return NULL;
    for (list_node_t *n = server->clients->head; n; n = n->next) {
        client = n->data;
        if (client && client->connected && client->type == CLIENT_GUI)
            return client;
    }
    return NULL;
}
