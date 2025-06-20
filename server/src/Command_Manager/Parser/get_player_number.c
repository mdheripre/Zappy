/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** get_player_number.c
*/

/****************************************************************************/
/*                                                                          */
/*                       HELPER GET PLAYER NUMBER                           */
/*                                                                          */
/****************************************************************************/

#include "utils.h"
#include <stdlib.h>

/**
 * @brief Extracts the player number from a string formatted as "#<number>".
 *
 * This function checks if the input string starts with '#' followed by digits.
 * If the format is correct, it converts the number part to an integer.
 *
 * @param str The input string containing the player number.
 * @return The player number as an integer, or -1 if the format is incorrect.
 */
int get_player_number(const char *str)
{
    if (!str)
        return -1;
    if (str[0] != '#' || !is_num(str + 1)) {
        console_log(LOG_WARNING, "Wrong player num format: %s", str);
        return -1;
    }
    return atoi(str + 1);
}
