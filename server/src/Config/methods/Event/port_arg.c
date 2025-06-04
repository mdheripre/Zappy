/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** port_arg.c
*/

#include "config.h"
#include "utils.h"
#include <ctype.h>

static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->port != -1) {
        parser->error_msg = "Multiple port definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing port number";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
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
    parser->index++;
    console_log(LOG_INFO, "Server port set to %d", config->port);
}
