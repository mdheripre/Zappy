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

/****************************************************************************/
/*                                                                          */
/*                        METHODS INITIALISATION                            */
/*                                                                          */
/****************************************************************************/

/**
 * LOG_COLORS - Array mapping log levels to their corresponding color codes.
 * Each index corresponds to a log level (LOG_INFO, LOG_SUCCESS, etc.)
 * and holds the ANSI color code string for that level.
 */
static const config_methods_t CONFIG_METHODS = {
    .destroy = config_destroy,
    .parse_args = parse_args,
    .is_int = is_int,
    .str_are_equals = str_are_equals,
    .is_float = is_float,
    .help_message = help_message
};

/****************************************************************************/
/*                                                                          */
/*                             EVENT REGISTER                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Registers all core command-line arguments.
 *
 * Associates known argument flags (like -p, -x, -n, etc.) with their
 * corresponding handler functions using the dispatcher.
 *
 * @param config Pointer to the configuration structure to update.
 */
static void register_core_args(config_t *config)
{
    REGISTER(config->dispatcher, EVENT_ARG_PORT, port_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_WIDTH, width_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_HEIGHT, height_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_TEAM_NAME, team_name_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_TEAM_SIZE, team_size_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_FREQUENCY, frequency_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_HELP_SHORT, help_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_HELP_LONG, help_arg, config);
    REGISTER(config->dispatcher, EVENT_ARG_HELP_ALT, help_arg, config);
}

/****************************************************************************/
/*                                                                          */
/*                             INITIALIZATION                               */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Initializes the fields of a config_t instance.
 *
 * Allocates internal structures (dispatcher and team list), sets default
 * invalid values for required fields, and registers supported arguments.
 *
 * @param config Pointer to the configuration to initialize.
 * @return true on success, false on allocation failure.
 */
static bool init_config(config_t *config)
{
    config->dispatcher = NEW(dispatcher, invalid_arg,
        EVENT_CLI_MAP, sizeof(EVENT_CLI_MAP) / sizeof(EVENT_CLI_MAP[0]));
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

/****************************************************************************/
/*                                                                          */
/*                                CONSTRUCTOR                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Creates and initializes a new configuration structure.
 *
 * Allocates memory for a config_t instance and sets up its methods and
 * internals. Frees and returns NULL on failure.
 *
 * @return Pointer to the newly allocated config_t, or NULL on failure.
 */
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
