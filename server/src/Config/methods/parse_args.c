/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** parse_args.c
*/

#include "config.h"
#include "shared.h"
#include "utils.h"
#include <stdbool.h>

static bool check_other_unset_values(config_t *config, parser_t *parser)
{
    if (config->frequency == -1.0f) {
        parser->error_msg = "Frequency is not set (-f)";
        return false;
    }
    if (config->team_name->size < 2) {
        parser->error_msg = "Need at least two teams (-n)";
        return false;
    }
    return true;
}

static bool check_unset_values(config_t *config, parser_t *parser)
{
    if (config->port == -1) {
        parser->error_msg = "Port is not set (-p)";
        return false;
    }
    if (config->width == -1) {
        parser->error_msg = "Width is not set (-x)";
        return false;
    }
    if (config->height == -1) {
        parser->error_msg = "Height is not set (-y)";
        return false;
    }
    if (config->team_size == -1) {
        parser->error_msg = "Team size is not set (-c)";
        return false;
    }
    return check_other_unset_values(config, parser);
}

static bool init_parser(config_t *config, parser_t *parser, int argc,
    char **argv)
{
    if (argc < 2) {
        console_log(LOG_ERROR, "No arguments provided");
        config->methods->help_message();
        return false;
    }
    parser->argc = argc;
    parser->argv = argv;
    parser->error = false;
    parser->error_msg = NULL;
    parser->index = 1;
    parser->free = false;
    return true;
}

bool parse_args(int argc, char **argv, config_t *config)
{
    parser_t parser;

    if (!init_parser(config, &parser, argc, argv))
        return false;
    for (; parser.index < argc; parser.index++) {
        EMIT(config->dispatcher, argv[parser.index], &parser);
        if (config->exit)
            return true;
        if (parser.error)
            console_log(LOG_ERROR, "Parse error: %s", parser.error_msg);
        if (parser.free)
            free(parser.error_msg);
        if (parser.error)
            return false;
    }
    if (!check_unset_values(config, &parser)) {
        console_log(LOG_ERROR, "Parse error: %s, see -h", parser.error_msg);
        return false;
    }
    return true;
}
