/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** update
*/

#include "player.h"
#include "game.h"
#include "client.h"

void player_update(player_t *self, game_t *game)
{
    game_event_t event = {
        .type = GAME_EVENT_PLAYER_DIED,
        .data.player_died.player_id = self->id,
        .data.player_died.client_fd = -1,
    };

    if (!self || !self->is_alive)
        return;
    self->nbr_tick++;
    if (self->nbr_tick < 126)
        return;
    self->nbr_tick = 0;
    if (self->inventory[RESOURCE_FOOD] > 0) {
        self->inventory[RESOURCE_FOOD]--;
    } else {
        self->methods->die(self);
        game->methods->add_event(game, event);
    }
}
