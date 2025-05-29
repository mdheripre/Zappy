/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_pop_event
*/

#include "game.h"

game_event_t *game_pop_event(game_t *self)
{
    if (!self)
        return NULL;
    return (game_event_t *)
        self->event_queue->methods->pop_front(self->event_queue);
}
