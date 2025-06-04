/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_ia_init
*/

#include "server.h"
#include "player.h"

static void send_player_init(server_t *server, client_t *client,
    const char *team_name)
{
    console_log(LOG_SUCCESS, "Client %d joined team \"%s\" as player #%d",
        client->fd, team_name, client->player->id);
    dprintf(client->fd, "%d %d\n", server->game->width, server->game->height);
    EMIT(server->command_manager->dispatcher, "command_ia_Connect_nbr",
        client);
}

static void init_player(server_t *server, client_t *client,
    const char *team_name)
{
    player_config_t config;

    config.x = 0;
    config.y = 0;
    config.orientation = 0;
    config.id = server->game->players->size + 1;
    config.team_name = team_name;
    client->player = NEW(player, config);
    if (!client->player)
        return;
    client->player = client->player;
    server->game->players->methods->push_back(server->game->players,
        client->player);
}

void on_ia_init(void *ctx, void *data)
{
    server_t *server = ctx;
    response_payload_t *payload = data;
    client_t *client = payload ? payload->client : NULL;
    const char *team_name = payload ? payload->message : NULL;
    player_t *player = NULL;

    if (!server || !client || !team_name)
        return;
    client->type = CLIENT_IA;
    if (!server->game->team_name->methods->contain(server->game->team_name,
        (void *)team_name, str_are_equals))
        return server->vtable->reject_client(server, client, "Unknown team");
    if (!(server->game->methods->count_team_members(server->game, team_name)
        < server->game->team_size))
        return reject_client(server, client, "No remaining slot");
    init_player(server, client, team_name);
    send_player_init(server, client, team_name);
}
