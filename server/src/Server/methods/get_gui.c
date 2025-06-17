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
    if (!server)
        return NULL;
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].connected &&
            server->clients[i].type == CLIENT_GUI)
            return &server->clients[i];
    }
    return NULL;
}
