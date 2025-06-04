/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** width.c
*/

#include "config.h"
#include "utils.h"
#include <ctype.h>

static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->width != -1) {
        parser->error_msg = "Multiple width definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing width value";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid width format";
        return false;
    }
    return true;
}

void width_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->width = atoi(parser->argv[parser->index + 1]);
    if (config->width <= 0) {
        parser->error_msg = "Width must be a positive integer";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "World width set to %d", config->width);
}
