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

void remove_client(server_t *self, client_t *client)
{
    player_t *player = NULL;

    if (!self || !client)
        return;
    if (client->player) {
        player = client->player;
        self->game->players->methods->remove(self->game->players, player);
        client->player = NULL;
    }
    console_log(LOG_INFO, "Client (fd=%d) disconnected", client->fd);
    close(client->fd);
    if (self->gui == client)
        self->gui = NULL;
    self->clients->methods->remove(self->clients, client);
}
