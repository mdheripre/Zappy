/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_client_connected
*/

#include "server.h"
#include "utils.h"

void on_client_connected(void *ctx, void *event_data)
{
    client_t *client = event_data;
    const char *welcome = "WELCOME\n";

    (void)ctx;
    console_log(LOG_INFO, "Event: client connected (fd=%d)", client->fd);
    write(client->fd, welcome, strlen(welcome));
}
