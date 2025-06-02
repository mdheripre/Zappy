/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_send_respons
*/

#include "server.h"

void on_send_response(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    response_payload_t *payload = (response_payload_t *)data;

    if (!server || !payload || !payload->client || !payload->message)
        return;
    write(payload->client->fd, payload->message, strlen(payload->message));
    free(payload->message);
    free(payload);
}
