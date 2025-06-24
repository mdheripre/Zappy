/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher
*/

#ifndef DISPATCHER_H_
    #define DISPATCHER_H_
    #define MAX_EVENT_HANDLERS EVENT_TYPE_COUNT
    #include <string.h>
    #include <stdlib.h>
    #include "event.h"
    #include <stdbool.h>

typedef void (*event_callback_t)(void *ctx, void *data);
typedef struct dispatcher_s dispatcher_t;
typedef struct event_handler_s event_handler_t;
typedef struct dispatcher_methods_s dispatcher_methods_t;
typedef void (*event_not_found_t)(dispatcher_t *self,
    const char *event, void *data);

struct event_handler_s {
    event_callback_t callback;
    void *ctx;
};

struct dispatcher_methods_s {
    void (*emit)(dispatcher_t *self, int index, void *data);
    bool (*register_event)(dispatcher_t *self, int index,
        event_callback_t callback, void *ctx);
};

struct dispatcher_s {
    event_handler_t handlers[MAX_EVENT_HANDLERS];
    const event_type_map_entry_t *map;
    size_t map_size;
    event_not_found_t on_not_found;
    const dispatcher_methods_t *vtable;
};

dispatcher_t *dispatcher_create(event_not_found_t default_not_found,
    const event_type_map_entry_t *map, size_t map_size);
void dispatcher_destroy(dispatcher_t *self);
bool dispatcher_register_event(dispatcher_t *self, int index,
    event_callback_t callback, void *ctx);
void dispatcher_emit(dispatcher_t *self, int index, void *data);
#endif /* !DISPATCHER_H_ */
