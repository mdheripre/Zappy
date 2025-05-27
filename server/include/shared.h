/*
** EPITECH PROJECT, 2025
** server
** File description:
** shared
*/


#ifndef SHARED_H_
    #define SHARED_H_
    #include <stdlib.h>
    #define MAX_GC_OBJECTS 1028
    #define NEW_CTOR(T, ...) T##_create(__VA_ARGS__)
    #define NEW_DTOR(T) (destructor_fn_t)T##_destroy
    #define NEW(T, ...) gc_new(NEW_CTOR(T, __VA_ARGS__), NEW_DTOR(T))
    #define DELETE() gc_cleanup()
    #define REGISTER(d, n, cb, ctx) (d)->vtable->register_event(d, n, cb, ctx)
    #define EMIT(d, n, data) (d)->vtable->emit(d, n, data)


typedef void (*destructor_fn_t)(void *);
typedef struct gc_entry_s gc_entry_t;
typedef struct gc_state_s gc_state_t;

struct gc_entry_s {
    void *ptr;
    destructor_fn_t destroy;
};

struct gc_state_s {
    gc_entry_t objects[MAX_GC_OBJECTS];
    int count;
};

void *gc_new(void *ptr, destructor_fn_t destroy);
void gc_register(void *ptr, destructor_fn_t destroy);
void gc_unregister(void *ptr);
void gc_cleanup(void);

#endif /* SHARED_H_ */
