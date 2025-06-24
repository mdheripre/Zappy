/*
** EPITECH PROJECT, 2025
** server
** File description:
** tna
*/

#include "client.h"
#include "command_manager.h"
#include "list.h"
#include "server.h"
#include "shared.h"
#include <stdio.h>

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Sends the team name to the GUI client via dprintf.
 *
 * @param client Pointer to the GUI client.
 * @param team Pointer to the team information.
 */
static void send_team_name_to_gui(client_t *client, team_info_t *team)
{
    if (!client || !team || !team->team_name)
        return;
    dprintf(client->fd, "tna %s\n", team->team_name);
}

/**
 * @brief Handles the GUI command "tna" by sending all team
 * names to the GUI client.
 *
 * @param ctx Pointer to the server context.
 * @param data Unused parameter.
 */
void handle_command_gui_tna(void *ctx, void *)
{
    server_t *server = ctx;
    client_t *client = server ? server->gui : NULL;
    team_info_t *team = NULL;

    if (!server || !client || !server->game || !server->game->teams)
        return;
    for (list_node_t *node = server->game->teams->head; node;
        node = node->next) {
        team = node->data;
        send_team_name_to_gui(client, team);
    }
}
