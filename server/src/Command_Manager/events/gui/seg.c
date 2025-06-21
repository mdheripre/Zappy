/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** seg
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

void handle_gui_seg(void *ctx, void *)
{
    server_t *server = ctx;
    client_t *gui = server->gui;
    char *winner = server->game->methods->get_winner(server->game);

    if (!gui)
        return;
    if (winner)
        dprintf(gui->fd, "seg %s\n", winner);
    else
        dprintf(gui->fd, "seg NULL\n");
    free(winner);
}
