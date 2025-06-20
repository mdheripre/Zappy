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
 * @brief Sends the team name to the GUI client.
 *
 * @param server Pointer to the server structure.
 * @param client Pointer to the GUI client.
 * @param team Pointer to the team information.
 */
static void send_team_name_to_gui(server_t *server, client_t *client,
    team_info_t *team)
{
    char buffer[BUFFER_COMMAND_SIZE];
    response_payload_t *payload = NULL;

    if (!team || !team->team_name)
        return;
    snprintf(buffer, sizeof(buffer), "tna %s\n", team->team_name);
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(buffer);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
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
    client_t *client = server->vtable->get_gui(server);
    team_info_t *team = NULL;

    if (!server || !client || !server->game || !server->game->teams)
        return;
    for (list_node_t *node = server->game->teams->head; node;
        node = node->next) {
        team = node->data;
        send_team_name_to_gui(server, client, team);
    }
}
