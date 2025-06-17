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
 * @brief Retrieve teams name index at passed index
 *
 * This function was usefull because the line were too long otherwise
 *
 * @param list Pointer to the list containing team names.
 * @param index Index of the team name to retrieve.
 * @return Pointer to the team name string at the specified index.
 */

static char *get_team_name(list_t *list, int index)
{
    return list->methods->index(list, index);
}

/**
 * @brief Sends tna response to the GUI client.
 *
 * Pass through all teams name and create a response payload for each
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the requesting GUI client.
 */
void handle_command_gui_tna(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    response_payload_t *payload;

    for (int i = 0; i < server->game->team_name->size; i++) {
        payload = malloc(sizeof(response_payload_t));
        if (!payload)
            return;
        asprintf(&payload->message, "tna %s\n",
            get_team_name(server->game->team_name, i));
        if (!payload->message) {
            free(payload);
            return;
        }
        payload->client = client;
        EMIT(server->dispatcher, "send_response", payload);
    }
    return;
}
