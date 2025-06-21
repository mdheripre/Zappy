/*
** EPITECH PROJECT, 2025
** server
** File description:
** pdr
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

void handle_gui_pdr(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = find_player_by_id(server->game,
        event->data.player_item.player_id);
    client_t *gui = server->gui;

    if (!server || !event || !player || !gui)
        return;
    dprintf(gui->fd, "pdr #%d %d\n", player->id,
        event->data.player_item.type_item);
}
