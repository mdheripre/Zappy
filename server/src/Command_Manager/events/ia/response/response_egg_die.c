/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_egg_die
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_egg_die(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;

    if (!server || !event)
        return;
    EMIT(server->command_manager->dispatcher, EVENT_GUI_EDI, event);
}
