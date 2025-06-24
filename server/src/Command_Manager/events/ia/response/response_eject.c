/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_eject
*/

#include "game.h"
#include "utils.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_eject(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    const char *msg = event->data.generic_response.response;
    client_t *client = event->data.generic_response.client;

    if (!server || !event || !client || !msg)
        return;
    dprintf(client->fd, "%s\n", msg);
    if (event->type == EVENT_RESP_PLAYER_OWNER_EJECTED &&
        strcmp(msg, "ok\n") == 0) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PEX, client);
    }
    if (event->type == EVENT_RESP_PLAYER_EJECTED)
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PPO,
            client->player);
    free((char *)event->data.generic_response.response);
}
