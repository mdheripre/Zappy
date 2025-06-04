/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** is_float.c
*/

#include <ctype.h>
#include <stdbool.h>

/****************************************************************************/
/*                                                                          */
/*                            HELPER METHODS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Checks if a decimal point in a float string is valid.
 *
 * @param arg The input string representing the number.
 * @param has_decimal A pointer to a bool tracking if a decimal has been seen.
 * @param index The current index in the string being validated.
 * @return true if the decimal placement is valid, false otherwise.
 */
static bool handle_decimal(char *arg, bool *has_decimal, int index)
{
    if (arg[index] == '.') {
        if (*has_decimal)
            return false;
        *has_decimal = true;
        if (arg[index + 1] == '\0')
            return false;
    }
    return true;
}

/**
 * @brief Verifies whether a given string is a valid float representation.
 *
 * Accepts optional sign, digits, and at most one decimal point.
 *
 * @param arg The string to validate.
 * @return true if the string is a valid float, false otherwise.
 */
bool is_float(char *arg)
{
    int index = (arg[0] == '-' || arg[0] == '+') ? 1 : 0;
    bool has_decimal = false;

    if (arg[index] == '\0')
        return false;
    for (; arg[index]; index++) {
        if (!handle_decimal(arg, &has_decimal, index))
            return false;
        if (arg[index] != '.' && !isdigit(arg[index]))
            return false;
    }
    return true;
}
