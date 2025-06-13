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
/*                          EGG MANAGEMENT                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Create a player from an egg and assign it to a client.
 *
 * @param server Pointer to the server.
 * @param client Pointer to the connecting client.
 * @param team_name Name of the player's team.
 * @param egg Pointer to the egg to hatch (can be NULL).
 */
static void init_player_from_egg(server_t *server, client_t *client,
    const char *team_name, egg_t *egg)
{
    player_config_t config;

    config.id = server->game->players->size + 1;
    config.x = egg ? egg->x : 0;
    config.y = egg ? egg->y : 0;
    config.orientation = (rand() % 4) + 1;
    config.team_name = team_name;
    client->player = NEW(player, config);
    if (!client->player)
        return;
    server->game->players->methods->push_back(server->game->players,
        client->player);
    if (egg)
        free(egg);
}

/**
 * @brief Log and notify the client of their initial game state.
 *
 * Sends map size and triggers Connect_nbr dispatch event.
 *
 * @param server Pointer to the server.
 * @param client Pointer to the initialized client.
 */
static void send_player_init(server_t *server, client_t *client)
{
    int used = server->game->methods->count_team_members(server->game,
        client->player->team_name);
    int available = server->game->team_size - used;

    console_log(LOG_SUCCESS, "Client %d joined team \"%s\" as player #%d",
        client->fd, client->player->team_name, client->player->id);
    dprintf(client->fd, "%d\n", available);
    dprintf(client->fd, "%d %d\n", server->game->width, server->game->height);
}

/**
 * @brief Predicate to match an egg with a given team name.
 *
 * @param a Pointer to an egg.
 * @param b Pointer to a team name (const char *).
 * @return true if the egg matches the team name.
 */
static bool match_egg(void *a, void *b)
{
    egg_t *egg = (egg_t *)a;
    const char *team = (const char *)b;

    if (!egg || !egg->team_name || !team)
        return false;
    return strcmp(egg->team_name, team) == 0;
}

/****************************************************************************/
/*                                                                          */
/*                          AI INITIALISATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Validate if a team exists and has available slots.
 *
 * Rejects the client if conditions are not met.
 *
 * @param server Pointer to the server.
 * @param team_name Name of the team.
 * @param client Pointer to the client.
 * @return true if the client must be rejected.
 */
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

/**
 * @brief Handle IA client initialization and assign an egg.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the payload with client and message.
 */
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
