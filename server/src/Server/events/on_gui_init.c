/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_gui_init
*/

#include "server.h"

void on_gui_init(void *ctx, void *data)
{
    server_t *server = ctx;
    response_payload_t *payload = data;
    client_t *client = payload->client;

    if (!server || !client)
        return;
    client->type = CLIENT_GUI;
    console_log(LOG_SUCCESS, "Client %d is GUI", client->fd);
    EMIT(server->command_manager->dispatcher, "command_gui_msz", client);
    EMIT(server->command_manager->dispatcher, "command_gui_sgt", client);
    EMIT(server->command_manager->dispatcher, "command_gui_mct", client);
}
