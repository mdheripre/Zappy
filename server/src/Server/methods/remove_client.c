/*
** EPITECH PROJECT, 2025
** server
** File description:
** remove_client
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                             CLIENT DELETE                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Removes a client from the server's client list.
 *
 * This function closes the client's file descriptor and removes the client
 * from the server's internal list of clients. It shifts remaining clients
 * down to fill the gap left by the removed client.
 *
 * @param self Pointer to the server instance.
 * @param index Index of the client to remove.
 */
void remove_client(server_t *self, int index)
{
    if (index < 0 || index >= self->client_count)
        return;
    close(self->clients[index].fd);
    for (int i = index; i < self->client_count - 1; i++)
        self->clients[i] = self->clients[i + 1];
    self->client_count--;
    console_log(LOG_INFO, "Client at index %d disconnected", index);
}
