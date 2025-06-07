/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** game_update_incantation
*/

#include "game.h"
#include "player.h"

static void send_end_incantation(game_t *self, incantation_t *inc)
{
    game_event_t *event = NULL;

    if (!self || !inc)
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    event->type = GAME_EVENT_END_INCANTATION;
    event->data.incantation.x = inc->x;
    event->data.incantation.y = inc->y;
    event->data.incantation.success = false;
    event->data.incantation.participants = inc->participants;
    self->methods->add_event(self, *event);
    free(event);
}

void update_incantations(game_t *self)
{
    list_node_t *curr = NULL;
    list_node_t *next = NULL;
    incantation_t *inc = NULL;

    if (!self || !self->incantations)
        return;
    curr = self->incantations->head;
    for (; curr; curr = next) {
        next = curr->next;
        inc = (incantation_t *)curr->data;
        if (!inc)
            continue;
        inc->tick_remaining--;
        if (inc->tick_remaining <= 0) {
            send_end_incantation(self, inc);
            self->incantations->methods->remove(self->incantations, inc);
        }
    }
}
