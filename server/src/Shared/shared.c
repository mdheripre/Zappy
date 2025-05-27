/*
** EPITECH PROJECT, 2025
** server
** File description:
** shared
*/

#include "shared.h"

/****************************************************************************/
/*                                                                          */
/*                             GARBAGE COLLECTOR                            */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Retrieves a pointer to the static garbage collector state.
 *
 * @return gc_state_t* Pointer to the singleton gc_state_t instance.
 */
static gc_state_t *get_gc_state(void)
{
    static gc_state_t gc = {0};

    return &gc;
}

/**
 * @brief Allocates a new object and registers it with the garbage collector.
 *
 * This function wraps the allocation of an object and registers it for
 * automatic cleanup when the garbage collector is invoked.
 *
 * @param ptr Pointer to the allocated object.
 * @param destroy Destructor function to call when cleaning up the object.
 * @return void* Pointer to the allocated object.
 */
void *gc_new(void *ptr, destructor_fn_t destroy)
{
    gc_register(ptr, destroy);
    return ptr;
}

/**
 * @brief Registers an object with the garbage collector.
 *
 * This function adds the object pointer and its destructor to the
 * garbage collector's internal list for cleanup.
 *
 * @param ptr Pointer to the object to register.
 * @param destroy Destructor function to call when cleaning up the object.
 */
void gc_register(void *ptr, destructor_fn_t destroy)
{
    gc_state_t *gc = get_gc_state();

    if (gc->count < MAX_GC_OBJECTS) {
        gc->objects[gc->count].ptr = ptr;
        gc->objects[gc->count].destroy = destroy;
        gc->count++;
    }
}

/**
 * @brief Shifts garbage collector entries to remove an object at a
 * specific index.
 *
 * This function shifts all entries in the garbage collector's object list
 * down by one position, effectively removing the entry at the specified index.
 *
 * @param gc Pointer to the garbage collector state.
 * @param index Index of the object to remove.
 */
static void shift_gc_entries(gc_state_t *gc, int index)
{
    for (int j = index; j < gc->count - 1; j++)
        gc->objects[j] = gc->objects[j + 1];
}

/**
 * @brief Unregisters an object from the garbage collector.
 *
 * This function searches for the specified object pointer in the garbage
 * collector's list and removes it if found, shifting subsequent entries down.
 *
 * @param ptr Pointer to the object to unregister.
 */
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

/**
 * @brief Cleans up all registered objects in the garbage collector.
 *
 * This function iterates through all registered objects, calls their
 * destructor functions if provided, and frees the memory allocated for them.
 * It resets the count of registered objects to zero after cleanup.
 */
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
