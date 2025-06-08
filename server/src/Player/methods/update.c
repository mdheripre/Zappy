/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** update
*/

#include "player.h"
#include "game.h"
#include "client.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                           PLAYER METHOD                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Add a player death event to the game's event queue.
 *
 * @param self Pointer to the player.
 * @param game Pointer to the game instance.
 */
static void add_event_died(player_t *self, game_t *game)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return;
    memset(event, 0, sizeof(game_event_t));
    event->type = GAME_EVENT_PLAYER_DIED;
    event->data.player_died.player_id = self->id;
    game->event_queue->methods->push_back(game->event_queue, event);
}

/**
 * @brief Update the player's hunger and trigger death if starving.
 *
 * @param self Pointer to the player.
 * @param game Pointer to the game instance.
 */
void player_update(player_t *self, game_t *game)
{
    if (!self || !self->is_alive || !game)
        return;
    self->nbr_tick++;
    if (self->nbr_tick == 110)
        console_log(LOG_WARNING, "Player %d is getting hungry!", self->id);
    if (self->nbr_tick < 126)
        return;
    self->nbr_tick = 0;
    if (self->inventory[RESOURCE_FOOD] > 0) {
        self->inventory[RESOURCE_FOOD]--;
        return;
    }
    self->methods->die(self);
    add_event_died(self, game);
}
