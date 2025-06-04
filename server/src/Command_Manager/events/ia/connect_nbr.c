/*
** EPITECH PROJECT, 2025
** server
** File description:
** connect_nbr
*/

#include "server.h"
#include "utils.h"
#include "player.h"

static void emit_response(server_t *server, client_t *client,
    const char *message)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));

    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(message);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}

void handle_command_connect_nbr(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    char buffer[BUFFER_SIZE] = {0};
    int used = 0;
    int slots = 0;

    if (!server || !client || !client->player)
        return;
    used = server->game->methods->count_team_members(server->game,
        client->player->team_name);
    slots = server->game->team_size - used;
    snprintf(buffer, sizeof(buffer), "%d\n", slots);
    emit_response(server, client, buffer);
}
