/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** team_size_arg.c
*/

#include "config.h"
#include "utils.h"
#include <ctype.h>

static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->team_size != -1) {
        parser->error_msg = "Multiple team size definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing team size value";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid team size format";
        return false;
    }
    return true;
}

void team_size_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->team_size = atoi(parser->argv[parser->index + 1]);
    if (config->team_size <= 0) {
        parser->error_msg = "Team size must be a positive integer";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "Team size set to %d", config->team_size);
}
