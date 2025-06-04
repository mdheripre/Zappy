/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Formats a tile's content into a BCT response string.
 *
 * Generates a message following the GUI protocol with the format:
 * "bct X Y q0 q1 q2 q3 q4 q5 q6\n", where X and Y are the coordinates
 * of the tile and qi represent the quantities of each resource type.
 *
 * @param tile Pointer to the tile to be formatted.
 * @return A dynamically allocated string containing the response,
 *         or NULL if the tile is NULL. The returned string must be freed
 *         by the caller.
 */
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

/**
 * @brief Sends a BCT response message to a GUI client.
 *
 * Uses the tile information to construct a BCT message and emits it
 * via the server's dispatcher to the specified GUI client. Handles
 * memory allocation and cleanup if formatting fails.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the GUI client that will receive the message.
 * @param tile Pointer to the tile whose content is to be sent.
 */
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

/**
 * @brief Handles the MCT command from a GUI client.
 *
 * Responds to the GUI request by sending the full content of the map,
 * tile by tile, using individual BCT responses for each tile. This allows
 * the client to reconstruct the current state of the entire game map.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the client that sent the MCT command
 * (cast from void).
 */
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
