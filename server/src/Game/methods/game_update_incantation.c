/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** game_update_incantation
*/

#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emit an event signaling the end of an incantation.
 *
 * @param self Pointer to the game instance.
 * @param inc Pointer to the incantation to end.
 */
static void send_end_incantation(game_t *self, incantation_t *inc)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!self || !inc || !event)
        return;
    event->type = GAME_EVENT_END_INCANTATION;
    event->data.incantation.x = inc->x;
    event->data.incantation.y = inc->y;
    event->data.incantation.success = false;
    event->data.incantation.participants = inc->participants;
    self->event_queue->methods->push_back(self->event_queue, event);
}

/**
 * @brief Update all active incantations by decrementing their timers.
 *
 * If an incantation has completed (tick_remaining ≤ 0), it is finalized
 * and removed from the list.
 *
 * @param self Pointer to the game instance.
 * @param ticks Number of ticks to subtract from each incantation.
 */
void update_incantations(game_t *self, int ticks)
{
    list_node_t *curr = self->incantations->head;
    list_node_t *next = NULL;
    incantation_t *inc = NULL;

    while (curr) {
        next = curr->next;
        inc = (incantation_t *)curr->data;
        if (!inc) {
            curr = next;
            continue;
        }
        inc->tick_remaining -= ticks;
        if (inc->tick_remaining <= 0) {
            send_end_incantation(self, inc);
            self->incantations->methods->remove(self->incantations, inc);
        }
        curr = next;
    }
}
