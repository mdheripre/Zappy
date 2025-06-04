/*
** EPITECH PROJECT, 2025
** server
** File description:
** connect_nbr
*/

#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             AI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emits a response message to a specific client via the dispatcher.
 *
 * Allocates and prepares a response payload with the given message and client,
 * then emits a "send_response" event through the server's dispatcher.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the target client.
 * @param message Null-terminated string to send as a response.
 */
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

/**
 * @brief Handles the Connect_nbr command from an AI client.
 *
 * Calculates the number of available slots for the requesting client's team
 * and sends it back as a numeric response. The response follows the format:
 * "N\n", where N is the number of available connection slots for the team.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting AI client (cast from void).
 */
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
