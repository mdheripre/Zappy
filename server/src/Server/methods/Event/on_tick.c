/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_tick
*/

#include "server.h"

#include "utils.h"

void on_tick(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;

    if (!client || client->type != CLIENT_IA)
        return;
    if (client->command_count == 0)
        return;
    client->commands[0].time_remaining -= 1.0f;
    if (client->commands[0].time_remaining <= 0.0f) {
        command_manager_handle(server, client,
            client->commands[0].content);
        for (int i = 1; i < client->command_count; i++)
            client->commands[i - 1] = client->commands[i];
        client->command_count--;
    }
}
