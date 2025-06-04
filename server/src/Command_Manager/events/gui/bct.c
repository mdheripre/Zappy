/*
** EPITECH PROJECT, 2025
** server
** File description:
** bct
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Formats the content of a map tile into a BCT response string.
 *
 * Constructs a message conforming to the GUI protocol in the form:
 * "bct X Y q0 q1 q2 q3 q4 q5 q6\n" where each qi represents the quantity
 * of a resource on the specified tile.
 *
 * @param tile Pointer to the tile whose contents will be formatted.
 * @return Dynamically allocated string containing the formatted BCT message.
 *         Must be freed by the caller.
 */
static char *format_bct_response(tile_t *tile)
{
    char buffer[BUFFER_COMMAND_SIZE];

    snprintf(buffer, sizeof(buffer), "bct %d %d %d %d %d %d %d %d %d\n",
        tile->x, tile->y, tile->resources[0], tile->resources[1],
        tile->resources[2], tile->resources[3], tile->resources[4],
        tile->resources[5], tile->resources[6]);
    return strdup(buffer);
}

/**
 * @brief Sends a BCT response to a GUI client.
 *
 * Allocates a response payload for the tile's content, formats it using
 * the BCT protocol, and emits a "send_response" event through the server's
 * dispatcher to forward it to the GUI client.
 *
 * @param server Pointer to the server instance.
 * @param client Target GUI client to send the response to.
 * @param tile Map tile to describe in the response.
 */
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

/**
 * @brief Validates and parses the arguments of a BCT command.
 *
 * Verifies that the incoming message is a correctly formatted BCT command
 * with two integer coordinates within the bounds of the game map.
 *
 * @param message The BCT command message to parse (will be freed if invalid).
 * @param x Output parameter for the parsed X coordinate.
 * @param y Output parameter for the parsed Y coordinate.
 * @param server Pointer to the server, used to validate map bounds.
 * @return true if the format is invalid or out of bounds, false otherwise.
 */
static bool check_format(char *message, int *x, int *y, server_t *server)
{
    if (strncmp(message, "bct ", 4) != 0 ||
        sscanf(message + 4, "%d %d", x, y) != 2) {
        free(message);
        return true;
    }
    if (*x < 0 || *x >= server->game->width || *y < 0 ||
        *y >= server->game->height) {
        free(message);
        return true;
    }
    return false;
}

/**
 * @brief Handles a BCT command from the GUI client.
 *
 * Parses and validates the incoming BCT message to retrieve a map tile's
 * coordinates. If valid, sends the tile's contents back to the client using
 * a properly formatted BCT response.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the request payload from the GUI client.
 */
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
