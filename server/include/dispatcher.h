/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher
*/

#ifndef DISPATCHER_H_
    #define DISPATCHER_H_
    #define MAX_EVENT_HANDLERS 128
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>

typedef void (*event_callback_t)(void *ctx, void *data);
typedef struct dispatcher_s dispatcher_t;
typedef struct event_handler_s event_handler_t;
typedef struct dispatcher_methods_s dispatcher_methods_t;

struct event_handler_s {
    const char *event_name;
    event_callback_t callback;
    void *ctx;
};

struct dispatcher_methods_s {
    void (*emit)(dispatcher_t *self, const char *event, void *data);
    bool (*register_event)(dispatcher_t *self, const char *event,
        event_callback_t callback, void *ctx);
};

struct dispatcher_s {
    event_handler_t handlers[MAX_EVENT_HANDLERS];
    int count;
    const dispatcher_methods_t *vtable;
};

dispatcher_t *dispatcher_create(void);
void dispatcher_destroy(dispatcher_t *self);
void dispatcher_emit(dispatcher_t *self, const char *event, void *data);
bool dispatcher_register(dispatcher_t *self,
    const char *event, event_callback_t callback, void *ctx);
#endif /* !DISPATCHER_H_ */
