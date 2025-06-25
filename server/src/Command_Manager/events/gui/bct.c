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
 * @brief Parse two integer coordinates (x, y) from a BCT command string.
 *
 * @param args String containing the coordinates.
 * @param x Output pointer for the X coordinate.
 * @param y Output pointer for the Y coordinate.
 * @return true if parsing was successful, false otherwise.
 */
static bool parse_bct_coords(const char *args, int *x, int *y)
{
    char *end = NULL;

    if (!args || !x || !y)
        return false;
    *x = strtol(args, &end, 10);
    if (!end || *end != ' ')
        return false;
    *y = strtol(end + 1, &end, 10);
    return (*end == '\0' || *end == '\n');
}

/**
 * @brief Send the contents of a tile to a GUI client in BCT format.
 *
 * Format: "bct X Y q0 q1 q2 q3 q4 q5 q6\n"
 *
 * @param client Pointer to the GUI client.
 * @param tile Pointer to the tile to send.
 */
static void send_bct_response(client_t *client, tile_t *tile)
{
    if (!client || !tile)
        return;
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n",
        tile->x, tile->y,
        tile->resources[0], tile->resources[1], tile->resources[2],
        tile->resources[3], tile->resources[4], tile->resources[5],
        tile->resources[6]);
}

/**
 * @brief Handle a GUI "bct X Y" command requesting tile content.
 *
 * Validates coordinates, parses input, and sends a BCT response.
 * If invalid, emits a "sbp" (syntax error) event to the GUI.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client issuing the command.
 */
void handle_command_gui_bct(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    const char *args = NULL;
    int x = 0;
    int y = 0;
    tile_t *tile = NULL;

    if (!server || !client || !server->game)
        return;
    args = extract_command_args(client_peek_command(client)->content);
    if (!parse_bct_coords(args, &x, &y) ||
        x < 0 || y < 0 ||
        x >= server->game->width || y >= server->game->height) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return;
    }
    tile = &server->game->map[y][x];
    send_bct_response(client, tile);
}
