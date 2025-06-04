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
    .parse_args = parse_args,
    .is_int = is_int,
    .str_are_equals = str_are_equals,
    .is_float = is_float,
    .help_message = help_message
};

static void register_core_args(config_t *config)
{
    REGISTER(config->dispatcher, "-p", port_arg, config);
    REGISTER(config->dispatcher, "-x", width_arg, config);
    REGISTER(config->dispatcher, "-y", height_arg, config);
    REGISTER(config->dispatcher, "-n", team_name_arg, config);
    REGISTER(config->dispatcher, "-c", team_size_arg, config);
    REGISTER(config->dispatcher, "-f", frequency_arg, config);
    REGISTER(config->dispatcher, "-h", help_arg, config);
    REGISTER(config->dispatcher, "--help", help_arg, config);
    REGISTER(config->dispatcher, "-help", help_arg, config);
}

static bool init_config(config_t *config)
{
    config->dispatcher = NEW(dispatcher, invalid_arg);
    if (!config->dispatcher) {
        console_log(LOG_ERROR, "Failed to create dispatcher");
        return false;
    }
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
    config->exit = false;
    register_core_args(config);
    return true;
}

config_t *config_create(void)
{
    config_t *config = malloc(sizeof(config_t));

    if (!config) {
        console_log(LOG_ERROR, "Failed to allocate memory for config");
        return NULL;
    }
    config->methods = &CONFIG_METHODS;
    if (!init_config(config)) {
        free(config);
        return NULL;
    }
    return config;
}
