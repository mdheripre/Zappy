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

/**
 * @brief Handles the response for an egg dying event.
 *
 * Emits the EVENT_GUI_EDI event to notify the GUI that an egg has died.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the event data (game_event_t).
 */
void on_response_egg_die(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;

    if (!server || !event)
        return;
    EMIT(server->command_manager->dispatcher, EVENT_GUI_EDI, event);
}
