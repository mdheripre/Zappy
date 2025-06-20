/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pfk
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

void handle_gui_pfk(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui = NULL;

    if (!server || !player)
        return;
    gui = server->vtable->get_gui(server);
    if (!gui)
        return;
    dprintf(gui->fd, "pfk #%d\n", player->id);
}
