/*
** EPITECH PROJECT, 2025
** server
** File description:
** shared
*/

#include "shared.h"

static gc_state_t *get_gc_state(void)
{
    static gc_state_t gc = {0};

    return &gc;
}

void *gc_new(void *ptr, destructor_fn_t destroy)
{
    gc_register(ptr, destroy);
    return ptr;
}

void gc_register(void *ptr, destructor_fn_t destroy)
{
    gc_state_t *gc = get_gc_state();

    if (gc->count < MAX_GC_OBJECTS) {
        gc->objects[gc->count].ptr = ptr;
        gc->objects[gc->count].destroy = destroy;
        gc->count++;
    }
}

static void shift_gc_entries(gc_state_t *gc, int index)
{
    for (int j = index; j < gc->count - 1; j++)
        gc->objects[j] = gc->objects[j + 1];
}

void gc_unregister(void *ptr)
{
    gc_state_t *gc = get_gc_state();

    for (int i = 0; i < gc->count; i++) {
        if (gc->objects[i].ptr == ptr) {
            shift_gc_entries(gc, i);
            gc->count--;
            return;
        }
    }
}

void gc_cleanup(void)
{
    gc_state_t *gc = get_gc_state();

    for (int i = gc->count - 1; i >= 0; i--) {
        if (gc->objects[i].destroy)
            gc->objects[i].destroy(gc->objects[i].ptr);
        free(gc->objects[i].ptr);
    }
    gc->count = 0;
}
