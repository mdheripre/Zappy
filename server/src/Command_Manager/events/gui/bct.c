/*
** EPITECH PROJECT, 2025
** server
** File description:
** bct
*/

#include "command_manager.h"
#include "event.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

static bool parse_bct_coords(const char *args, int *x, int *y)
{
    char *end = NULL;

    if (!args || !x || !y)
        return false;
    *x = strtol(args, &end, 10);
    if (!end || *end != ' ')
        return false;
    *y = strtol(end + 1, NULL, 10);
    return true;
}

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
    if (!parse_bct_coords(args, &x, &y))
        return EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
    if (x < 0 || y < 0 || x >= server->game->width ||
        y >= server->game->height)
        return EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
    tile = &server->game->map[y][x];
    send_bct_response(client, tile);
}
