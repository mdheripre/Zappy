/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** height_arg.c
*/

#include "config.h"
#include "utils.h"
#include <ctype.h>

static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->height != -1) {
        parser->error_msg = "Multiple height definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing height value";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid height format";
        return false;
    }
    return true;
}

void height_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->height = atoi(parser->argv[parser->index + 1]);
    if (config->height <= 0) {
        parser->error_msg = "Height must be a positive integer";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "World height set to %d", config->height);
}
