/*
** EPITECH PROJECT, 2025
** server
** File description:
** bct
*/

#include "command_manager.h"


static char *format_bct_response(tile_t *tile)
{
    char buffer[BUFFER_COMMAND_SIZE];

    snprintf(buffer, sizeof(buffer), "bct %d %d %d %d %d %d %d %d %d\n",
        tile->x, tile->y, tile->resources[0], tile->resources[1],
        tile->resources[2], tile->resources[3], tile->resources[4],
        tile->resources[5], tile->resources[6]);
    return strdup(buffer);
}

static void send_bct_response(server_t *server, client_t *client, tile_t *tile)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));

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

static bool check_format(char *message, int *x, int *y, server_t *server)
{
    if (strncmp(message, "bct ", 4) != 0 ||
        sscanf(message + 4, "%d %d", x, y) != 2) {
        free(message);
        return true;
    }
    if (x < 0 || x >= server->game->width || y < 0 ||
        y >= server->game->height) {
        free(message);
        return true;
    }
    return false;
}

void handle_command_gui_bct(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    response_payload_t *req = (response_payload_t *)data;
    int x = 0;
    int y = 0;
    char *message = NULL;

    if (!server || !req || !req->client || !req->message)
        return;
    message = strdup(req->message);
    if (!message)
        return;
    strip_linefeed(message);
    if (check_format(message, &x, &y, server)) {
        free(message);
        return;
    }
    send_bct_response(server, req->client, &server->game->map[y][x]);
    free(message);
}
