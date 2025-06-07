/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** command_manager_process_response
*/

#include "command_manager.h"
#include "game.h"
#include "utils.h"

void process_responses(command_manager_t *self, game_t *game)
{
    game_event_t *event = NULL;
    const char *event_name = NULL;

    if (!self || !self->dispatcher || !game || !game->server_event_queue)
        return;
    for (event = game->server_event_queue->methods->
        pop_front(game->server_event_queue); event != NULL; event =
        game->server_event_queue->methods
        ->pop_front(game->server_event_queue)) {
        event_name = event_type_name(event->type);
        EMIT(self->dispatcher, event_name, event);
        free(event);
    }
}
