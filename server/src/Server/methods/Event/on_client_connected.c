/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_client_connected
*/

#include "server.h"
#include "utils.h"


/****************************************************************************/
/*                                                                          */
/*                           EVENT PUBLIC                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the client connection event.
 *
 * This function is called when a new client connects to the server.
 * It sends a welcome message to the client and logs the connection.
 *
 * @param ctx Unused context pointer.
 * @param event_data Pointer to the client_t structure representing the
 * connected client.
 */
void on_client_connected(void *ctx, void *event_data)
{
    client_t *client = event_data;
    const char *welcome = "WELCOME\n";

    (void)ctx;
    console_log(LOG_INFO, "Event: client connected (fd=%d)", client->fd);
    write(client->fd, welcome, strlen(welcome));
}
