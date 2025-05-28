/*
** EPITECH PROJECT, 2025
** server
** File description:
** strip_linefeed
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                                 UTILS                                    */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Strips the trailing newline character from a string.
 *
 * This function modifies the input string by replacing the last character
 * with a null terminator if it is a newline character.
 *
 * @param line Pointer to the string to modify.
 */
void strip_linefeed(char *line)
{
    size_t len = strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}
