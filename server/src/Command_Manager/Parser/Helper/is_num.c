/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** is_num.c
*/

/****************************************************************************/
/*                                                                          */
/*                              IS NUM HELPER                               */
/*                                                                          */
/****************************************************************************/

#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Checks if a string represents a valid number.
 *
 * A valid number consists only of digits (0-9).
 * This function does not handle negative numbers or decimal points.
 *
 * @param arg The string to check.
 * @return true if the string is a valid number, false otherwise.
 */
bool is_num(const char *arg)
{
    if (!arg || !arg[0])
        return false;
    for (int i = 0; arg[i]; ++i) {
        if (!isdigit(arg[i]))
            return false;
    }
    return true;
}
