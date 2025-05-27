/*
** EPITECH PROJECT, 2025
** server
** File description:
** strip_linefeed
*/

#include "server.h"

void strip_linefeed(char *line)
{
    size_t len = strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}
