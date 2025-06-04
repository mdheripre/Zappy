/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** invalid_arg.c
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "dispatcher.h"

/****************************************************************************/
/*                                                                          */
/*                              EVENTS FLAGS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handler for unrecognized command-line arguments.
 *
 * Sets the parser in error mode and stores a formatted message
 * indicating the invalid argument, suggesting to use `-h`.
 *
 * @param dispatcher Unused dispatcher pointer.
 * @param event_data The unrecognized argument string.
 * @param data Pointer to the parser context.
 */
void invalid_arg(dispatcher_t *, const char *event_data, void *data)
{
    parser_t *parser = data;

    parser->error = true;
    asprintf(&parser->error_msg, "Invalid argument: %s, see -h", event_data);
    parser->free = true;
}
