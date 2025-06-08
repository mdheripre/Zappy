/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** die
*/

#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                           PLAYER METHOD                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Mark the player as dead and log the event.
 *
 * @param self Pointer to the player.
 */
void player_die(player_t *self)
{
    if (!self)
        return;
    self->is_alive = false;
    console_log(LOG_INFO, "Player %d died", self->id);
}
