/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pdi
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

void handle_gui_pdi(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui = server->gui;

    if (!server || !player || !gui)
        return;
    dprintf(gui->fd, "pdi #%d\n", player->id);
}
