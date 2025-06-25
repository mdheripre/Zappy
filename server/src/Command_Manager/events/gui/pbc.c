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
/**
 * @brief Handles the "pbc" (broadcast) event for the GUI client.
 *
 * Sends a broadcast message from a player to the GUI client and frees
 * the response string.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the event data (game_event_t).
 */
void handle_gui_pbc(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *gui = server ? server->gui : NULL;
    char *msg = event ? (char *)event->data.generic_response.response : NULL;

    if (!server || !event || !msg || !event->data.generic_response.client ||
        !event->data.generic_response.client->player || !gui) {
        free(msg);
        return;
    }
    dprintf(gui->fd, "pbc #%d %s\n",
        event->data.generic_response.client->player->id,
        msg);
    free(msg);
}
