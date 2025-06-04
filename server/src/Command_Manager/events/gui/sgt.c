/*
** EPITECH PROJECT, 2025
** server
** File description:
** sgt
*/

#include "command_manager.h"

void handle_command_gui_sgt(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    char buffer[BUFFER_COMMAND_SIZE];
    response_payload_t *payload = malloc(sizeof(response_payload_t));

    if (!payload)
        return;
    snprintf(buffer, sizeof(buffer), "sgt %d\n", (int)server->game->frequency);
    payload->client = client;
    payload->message = strdup(buffer);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
