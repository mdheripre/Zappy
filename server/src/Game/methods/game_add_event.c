/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_add_event
*/

#include "game.h"

void game_add_event(game_t *self, game_event_t event)
{
    game_event_t *copy = malloc(sizeof(game_event_t));

    if (!self || !copy)
        return;
    *copy = event;
    self->event_queue->methods->push_back(self->event_queue, copy);
}
