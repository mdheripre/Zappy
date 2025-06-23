/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pie
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


void handle_gui_pie(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *gui = NULL;
    int x;
    int y;
    int result;

    if (!server || !event)
        return;
    gui = server->gui;
    if (!gui)
        return;
    x = event->data.incantation.x;
    y = event->data.incantation.y;
    result = event->data.incantation.success ? 1 : 0;
    dprintf(gui->fd, "pie %d %d %d\n", x, y, result);
}
