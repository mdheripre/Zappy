/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** port_arg.c
*/

#include "config.h"
#include <ctype.h>

static bool check_format(char *arg)
{
    int index = (arg[0] == '-' || arg[0] == '+') ? 1 : 0;

    for (; arg[index] != '\0'; index++) {
        if (!isdigit(arg[index])) {
            return false;
        }
    }
    return true;
}

static bool check_errors(config_t *config, parser_t *parser)
{
    if (config->port != -1) {
        parser->error_msg = "Multiple port definitions";
        return false;
    }
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing port number";
        return false;
    }
    if (!check_format(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid port number format";
        return false;
    }
    return true;
}

void port_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->port = atoi(parser->argv[parser->index + 1]);
    if ((config->port < 1024 && config->port != 0) || config->port > 65535) {
        parser->error_msg = "Port number must be between 1024 and 65535";
        parser->error = true;
        return;
    }
}
