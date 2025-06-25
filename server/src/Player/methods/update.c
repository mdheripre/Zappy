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
    event->type = EVENT_PLAYER_DIED;
    event->data.player_died.player = self;
    game->event_queue->methods->push_back(game->event_queue, event);
}

/**
 * @brief Adds a "player eat" event to the server event queue.
 *
 * Allocates and initializes a game_event_t for a player eating action,
 * then pushes it to the server's event queue.
 *
 * @param self Pointer to the player triggering the event.
 * @param game Pointer to the game context.
 */
static void add_event_player_eat(player_t *self, game_t *game)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return;
    memset(event, 0, sizeof(game_event_t));
    event->type = EVENT_RESP_PLAYER_EAT;
    event->data.generic_response.client = self->client;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        event);
}

/**
 * @brief Update a player's hunger and handle starvation logic.
 *
 * Increments tick counter and consumes food. If starving, triggers death.
 *
 * @param self Pointer to the player.
 * @param game Pointer to the game instance.
 * @param ticks Number of ticks since the last update.
 */
void player_update(player_t *self, game_t *game, int ticks)
{
    if (!self || !self->is_alive || !game)
        return;
    self->nbr_tick += ticks;
    if (self->nbr_tick >= 110 && self->inventory[RESOURCE_FOOD] <= 0)
        console_log(LOG_WARNING, "Player %d is getting hungry!", self->id);
    if (self->nbr_tick < 126)
        return;
    self->nbr_tick = 0;
    if (self->inventory[RESOURCE_FOOD] > 0) {
        self->inventory[RESOURCE_FOOD]--;
        add_event_player_eat(self, game);
        return;
    }
    self->methods->die(self);
    add_event_died(self, game);
}
