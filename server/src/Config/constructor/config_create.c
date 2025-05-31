/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** config_create.c
*/

#include "config.h"
#include "shared.h"
#include "utils.h"
#include <bits/getopt_core.h>
#include <stdbool.h>
#include <stdlib.h>

static const config_methods_t CONFIG_METHODS = {
    .destroy = config_destroy,
};

static void register_core_args(config_t *config)
{
    REGISTER(config->dispatcher, "-p", port_arg, config);
}

static bool parse_args(int argc, char **argv, config_t *config)
{
    parser_t parser;

    parser.argc = argc;
    parser.argv = argv;
    parser.error = false;
    parser.error_msg = NULL;
    for (parser.index = 1; parser.index < argc; parser.index++) {
        EMIT(config->dispatcher, argv[parser.index], &parser);
        if (parser.error) {
            console_log(LOG_ERROR, "Parse error: %s", parser.error_msg);
            return false;
        }
    }
    return true;
}

bool init_config(config_t *config)
{

    config->team_name = NEW(list, free);
    if (!config->team_name) {
        console_log(LOG_ERROR, "Failed to create team name list");
        return false;
    }
    config->height = -1;
    config->width = -1;
    config->team_size = -1;
    config->port = -1;
    config->frequency = -1.0f;
    register_core_args(config);
    return true;
}

config_t *config_create(int argc, char **argv)
{
    config_t *config = malloc(sizeof(config_t));

    if (!config)
        return NULL;
    config->methods = &CONFIG_METHODS;
    if (!init_config(config)) {
        free(config);
        return NULL;
    }
    if (!parse_args(argc, argv, config)) {
        free(config);
        return NULL;
    }
    return config;
}
