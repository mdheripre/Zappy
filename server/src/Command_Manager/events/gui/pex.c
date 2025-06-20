/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pex
*/

#include "command_manager.h"
#include "shared.h"
#include "server.h"
#include "client.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

void handle_gui_pex(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = client->player;
    client_t *gui = server_get_gui(server);

    if (!server || !client || !player || !gui)
        return;
    dprintf(gui->fd, "pex #%d\n", player->id);
}
