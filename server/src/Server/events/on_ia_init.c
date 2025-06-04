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

/**
 * @brief Sends initial information to a newly connected AI client.
 *
 * Logs the team and ID assignment, sends map size via dprintf, and
 * emits the Connect_nbr command to inform the client of available slots.
 *
 * @param server Pointer to the server.
 * @param client Pointer to the newly accepted AI client.
 * @param team_name Name of the team the client joined.
 */
static void send_player_init(server_t *server, client_t *client,
    const char *team_name)
{
    console_log(LOG_SUCCESS, "Client %d joined team \"%s\" as player #%d",
        client->fd, team_name, client->player->id);
    dprintf(client->fd, "%d %d\n", server->game->width, server->game->height);
    EMIT(server->command_manager->dispatcher, "command_ia_Connect_nbr",
        client);
}

/**
 * @brief Initializes a new player instance and attaches it to a client.
 *
 * Creates a new player with a unique ID and starting position, then
 * adds the player to the game's player list.
 *
 * @param server Pointer to the server.
 * @param client Pointer to the client to bind the player to.
 * @param team_name Team name assigned to the player.
 */
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

/**
 * @brief Initializes an AI client after connection.
 *
 * Validates the requested team, checks slot availability, creates and
 * assigns a new player, and sends initialization info. Rejects the client
 * if validation fails.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the response payload containing client and team name.
 */
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
