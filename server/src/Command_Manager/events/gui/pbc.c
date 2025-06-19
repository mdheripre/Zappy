/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pbc
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

void handle_gui_pbc(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *gui = server->vtable->get_gui(server);

    if (!server || !event || !gui || !event->data.generic_response.response)
        return;
    dprintf(gui->fd, "pbc #%d %s\n",
        event->data.generic_response.player_id,
        event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
