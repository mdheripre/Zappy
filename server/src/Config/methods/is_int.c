/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** is_int.c
*/

#include <ctype.h>
#include <stdbool.h>

/****************************************************************************/
/*                                                                          */
/*                            HELPER METHODS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Checks if a string represents a valid integer.
 *
 * Supports optional leading '+' or '-' signs. A valid integer must contain
 * at least one digit and only digits (after the sign).
 *
 * @param arg The string to check.
 * @return true if the string is a valid integer, false otherwise.
 */
bool is_int(char *arg)
{
    int index = (arg[0] == '-' || arg[0] == '+') ? 1 : 0;

    if (arg[index] == '\0')
        return false;
    for (; arg[index] != '\0'; index++) {
        if (!isdigit(arg[index])) {
            return false;
        }
    }
    return true;
}
