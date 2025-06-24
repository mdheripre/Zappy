/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pmv
*/

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

#include "client.h"
#include "command_manager.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>

void handle_gui_pmv(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui = NULL;

    if (!server || !player)
        return;
    gui = server->gui;
    if (!gui)
        return;
    dprintf(gui->fd, "smg pmv #%d\n", player->id);
}
