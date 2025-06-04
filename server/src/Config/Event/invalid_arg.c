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


void invalid_arg(dispatcher_t *, const char *event_data, void *data)
{
    parser_t *parser = data;

    parser->error = true;
    asprintf(&parser->error_msg, "Invalid argument: %s, see -h", event_data);
    parser->free = true;
}
