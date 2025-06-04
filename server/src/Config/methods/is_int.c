/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** is_int.c
*/

#include <ctype.h>
#include <stdbool.h>

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
