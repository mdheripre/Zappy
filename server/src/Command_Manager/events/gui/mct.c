/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"

static char *format_bct_response(const tile_t *tile)
{
    char buffer[BUFFER_COMMAND_SIZE];

    if (!tile)
        return NULL;
    snprintf(buffer, sizeof(buffer),
        "bct %d %d %d %d %d %d %d %d %d\n",
        tile->x, tile->y,
        tile->resources[0], tile->resources[1], tile->resources[2],
        tile->resources[3], tile->resources[4], tile->resources[5],
        tile->resources[6]);
    return strdup(buffer);
}

static void send_bct_response(server_t *server, client_t *client,
    const tile_t *tile)
{
    response_payload_t *payload = NULL;

    if (!server || !client || !tile)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = format_bct_response(tile);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}

void handle_command_gui_mct(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    tile_t *tile = NULL;

    if (!server || !client || !server->game)
        return;
    for (int y = 0; y < server->game->height; y++) {
        for (int x = 0; x < server->game->width; x++) {
            tile = &server->game->map[y][x];
            send_bct_response(server, client, tile);
            usleep(1);
        }
    }
}
