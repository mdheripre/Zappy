/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** is_float.c
*/

#include <ctype.h>
#include <stdbool.h>

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
