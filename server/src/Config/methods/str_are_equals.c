/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** str_are_equals.c
*/

#include <stdbool.h>

bool str_are_equals(void *data1, void *data2)
{
    char *str1 = data1;
    char *str2 = data2;
    int i;

    if (!str1 || !str2)
        return false;
    for (i = 0; str1[i] && str2[i]; i++) {
        if (str1[i] != str2[i])
            return false;
    }
    return str1[i] == str2[i];
}
