/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_ia_init
*/

#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                          AI INITIALISATION                               */
/*                                                                          */
/****************************************************************************/

static void init_player_from_egg(server_t *server, client_t *client,
    const char *team_name, egg_t *egg)
{
    player_config_t config;

    config.id = server->game->players->size + 1;
    config.x = egg ? egg->x : 0;
    config.y = egg ? egg->y : 0;
    config.orientation = 0;
    config.team_name = team_name;
    client->player = NEW(player, config);
    if (!client->player)
        return;
    server->game->players->methods->push_back(server->game->players,
        client->player);
    if (egg)
        free(egg);
}

static void send_player_init(server_t *server, client_t *client)
{
    console_log(LOG_SUCCESS, "Client %d joined team \"%s\" as player #%d",
        client->fd, client->player->team_name, client->player->id);
    EMIT(server->command_manager->dispatcher, "command_ia_Connect_nbr",
        client);
    dprintf(client->fd, "%d %d\n", server->game->width, server->game->height);
}

static bool match_egg(void *a, void *b)
{
    egg_t *egg = (egg_t *)a;
    const char *team = (const char *)b;

    if (!egg || !egg->team_name || !team)
        return false;
    return strcmp(egg->team_name, team) == 0;
}

static bool check_condition(server_t *server, const char *team_name,
    client_t *client)
{
    if (!server->game->team_name->methods->contain(
            server->game->team_name, (void *)team_name, str_are_equals)) {
        server->vtable->reject_client(server, client, "Unknown team");
        return true;
    }
    if (server->game->methods->count_team_members(server->game, team_name)
        >= server->game->team_size) {
        server->vtable->reject_client(server, client, "No remaining slot");
        return true;
    }
    return false;
}

void on_ia_init(void *ctx, void *data)
{
    server_t *server = ctx;
    response_payload_t *payload = data;
    client_t *client = payload ? payload->client : NULL;
    const char *team_name = payload ? payload->message : NULL;
    egg_t *egg = NULL;

    if (!server || !client || !team_name)
        return;
    client->type = CLIENT_IA;
    if (check_condition(server, team_name, client))
        return;
    egg = server->game->eggs->methods->consume(
        server->game->eggs, match_egg, (void *)team_name);
    if (!egg) {
        server->vtable->reject_client(server, client, "No egg available");
        return;
    }
    init_player_from_egg(server, client, team_name, egg);
    send_player_init(server, client);
}
