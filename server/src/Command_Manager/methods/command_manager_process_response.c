/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** command_manager_process_response
*/

#include "command_manager.h"
#include "game.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                       PROCESS RESPONSE                                   */
/*                                                                          */
/****************************************************************************/


/**
 * Process game events queued for server responses.
 *
 * Pops all events from the server_event_queue and emits them.
 *
 * @param self Command manager handling the dispatcher.
 * @param game Game instance containing the event queue.
 */
void process_responses(command_manager_t *self, game_t *game)
{
    game_event_t *event = NULL;

    if (!self || !self->dispatcher || !game || !game->server_event_queue)
        return;
    for (event = game->server_event_queue->methods->
        pop_front(game->server_event_queue); event != NULL;
        event = game->server_event_queue->methods->
        pop_front(game->server_event_queue)) {
        EMIT(self->dispatcher, event->type, event);
        free(event);
    }
}
