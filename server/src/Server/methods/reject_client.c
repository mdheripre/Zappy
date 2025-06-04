/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** reject_client
*/

#include "server.h"


void reject_client(server_t *server, client_t *client, const char *reason)
{
    write(client->fd, "ko\n", 3);
    console_log(LOG_WARNING, "%s (fd=%d)", reason, client->fd);
    for (int i = 0; i < server->client_count; i++) {
        if (&server->clients[i] == client) {
            server->vtable->remove_client(server, i);
            return;
        }
    }
}
