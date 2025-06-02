/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatch_game_event
*/


#include "game.h"
#include "server.h"
#include "dispatcher.h"
#include "client.h"
#include "shared.h"

const char *event_type_name(game_event_type_t type)
{
    for (size_t i = 0;
        i < sizeof(EVENT_TYPE_MAP) / sizeof(EVENT_TYPE_MAP[0]); i++) {
        if (EVENT_TYPE_MAP[i].type == type)
            return EVENT_TYPE_MAP[i].name;
    }
    return "UNKNOWN";
}

void game_dispatch_events(game_t *self)
{
    game_event_t *event = NULL;
    const char *event_name = NULL;

    if (!self || !self->dispatcher)
        return;
    event = self->methods->pop_event(self);
    while (event) {
        event_name = event_type_name(event->type);
        EMIT(self->dispatcher, event_name, event);
        free(event);
        event = self->methods->pop_event(self);
    }
}
