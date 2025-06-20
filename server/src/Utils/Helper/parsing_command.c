/*
** EPITECH PROJECT, 2025
** server
** File description:
** parsing_command
*/

#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Extract the command name from a line.
 *
 * Copies the first word into the output buffer.
 *
 * @param line Input string containing the command line.
 * @param out Output buffer to store the command name.
 * @param size Size of the output buffer.
 * @return Pointer to the output buffer, or NULL on error.
 */
char *extract_command_name(const char *line, char *out, size_t size)
{
    size_t i = 0;

    if (!line || !out || size == 0)
        return NULL;
    while (line[i] != '\0' && line[i] != ' ' && i < size - 1) {
        out[i] = line[i];
        i++;
    }
    out[i] = '\0';
    return out;
}

/**
 * @brief Return a pointer to the argument part of a command line.
 *
 * @param line Input string containing the command line.
 * @return Pointer to the argument part, or NULL if not found.
 */
const char *extract_command_args(const char *line)
{
    size_t i = 0;

    if (!line)
        return NULL;
    while (line[i] != '\0' && line[i] != ' ')
        i++;
    while (line[i] == ' ')
        i++;
    return line[i] ? &line[i] : NULL;
}

/**
 * @brief Copy the argument part of a command line into a buffer.
 *
 * @param line Input command line.
 * @param out Output buffer to store the arguments.
 * @param out_size Size of the output buffer.ppo #n
 * @return true on success, false on error.
 */
bool extract_command_arguments(const char *line, char *out, size_t out_size)
{
    const char *args = extract_command_args(line);

    if (!line || !out || out_size == 0 || !args)
        return false;
    snprintf(out, out_size, "%s", args);
    out[out_size - 1] = '\0';
    return true;
}

/**
 * @brief Get the next argument from a command line.
 *
 * This function extracts the first argument from the line, copies it to the
 * provided buffer, and removes it from the line.
 *
 * @param line Input command line string.
 * @param arg Output buffer for the extracted argument.
 * @param arg_size Size of the output buffer.
 * @return true if an argument was extracted, false if no more arguments
 */
bool get_next_arg(char *line, char *arg, int arg_size)
{
    int size;

    if (arg)
        arg[0] = '\0';
    if (!line || !arg || arg_size <= 1)
        return false;
    for (size = 0; line[size] && line[size] != ' '; ++size);
    if (size == 0)
        return false;
    if (size >= arg_size) {
        console_log(LOG_WARNING, "Buffer arg Overflow: %s", line);
        return false;
    }
    memcpy(arg, line, size);
    arg[size] = '\0';
    for (; line[size] == ' '; ++size);
    memmove(line, line + size, strlen(line + size) + 1);
    return true;
}
