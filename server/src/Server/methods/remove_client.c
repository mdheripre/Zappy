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


void remove_client(server_t *self, int index)
{
    client_t *client = NULL;
    player_t *player = NULL;

    if (index < 0 || index >= self->client_count)
        return;
    client = &self->clients[index];
    if (client->player) {
        player = client->player;
        self->game->players->methods->remove(self->game->players, player);
        client->player = NULL;
    }
    close(client->fd);
    for (int i = index; i < self->client_count - 1; i++)
        self->clients[i] = self->clients[i + 1];
    self->client_count--;
    console_log(LOG_INFO, "Client at index %d disconnected", index);
}
