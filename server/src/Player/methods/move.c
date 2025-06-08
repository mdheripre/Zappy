/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** move
*/

#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                           PLAYER METHOD                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Move the player forward based on orientation.
 *
 * Handles map wrapping horizontally and vertically.
 *
 * @param self Pointer to the player.
 * @param map_width Width of the map.
 * @param map_height Height of the map.
 */
static void move_forward(player_t *self, int map_width, int map_height)
{
    switch (self->orientation) {
        case ORIENTATION_NORTH:
            self->y = (self->y - 1 + map_height) % map_height;
            break;
        case ORIENTATION_EAST:
            self->x = (self->x + 1) % map_width;
            break;
        case ORIENTATION_SOUTH:
            self->y = (self->y + 1) % map_height;
            break;
        case ORIENTATION_WEST:
            self->x = (self->x - 1 + map_width) % map_width;
            break;
    }
}

/**
 * @brief Rotate the player 90° to the left (counter-clockwise).
 *
 * @param self Pointer to the player.
 */
static void turn_left(player_t *self)
{
    self->orientation--;
    if (self->orientation < ORIENTATION_NORTH)
        self->orientation = ORIENTATION_WEST;
}

/**
 * @brief Rotate the player 90° to the right (clockwise).
 *
 * @param self Pointer to the player.
 */
static void turn_right(player_t *self)
{
    self->orientation++;
    if (self->orientation > ORIENTATION_WEST)
        self->orientation = ORIENTATION_NORTH;
}

/**
 * @brief Move or rotate the player according to the given direction.
 *
 * @param self Pointer to the player.
 * @param map_width Width of the map.
 * @param map_height Height of the map.
 * @param dir Direction of movement.
 */
void player_move(player_t *self, int map_width, int map_height,
    move_direction_t dir)
{
    if (!self || !self->is_alive)
        return;
    switch (dir) {
        case MOVE_FORWARD:
            move_forward(self, map_width, map_height);
            break;
        case TURN_LEFT:
            turn_left(self);
            break;
        case TURN_RIGHT:
            turn_right(self);
            break;
    }
}
