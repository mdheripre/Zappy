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

/**
 * @brief Handles the GUI "seg" event, notifying the GUI client of
 * the game winner.
 *
 * This function retrieves the winner of the game and sends a "seg" message
 * to the GUI client. If there is no winner, it sends "seg NULL".
 *
 * @param ctx Pointer to the server context (server_t *)
 * @param Unused parameter
 */
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
