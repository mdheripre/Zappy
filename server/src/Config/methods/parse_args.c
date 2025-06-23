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

/****************************************************************************/
/*                                                                          */
/*                            PARSER METHODS                                */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Checks if optional values are set correctly in config.
 *
 * Verifies that the frequency is set and that there are at least
 * two team names registered.
 *
 * @param config The configuration object.
 * @param parser The parser instance (used for setting error_msg).
 * @return true if all optional values are valid, false otherwise.
 */
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

/**
 * @brief Checks if all required configuration values are set.
 *
 * This includes port, map size (width/height), team size,
 * and delegates frequency/team validation to another checker.
 *
 * @param config The configuration object.
 * @param parser The parser instance (used for setting error_msg).
 * @return true if all required values are present, false otherwise.
 */
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

/**
 * @brief Initializes the argument parser before parsing begins.
 *
 * Ensures that the argument list is not empty, and sets up
 * parser values such as argc, argv, and default states.
 *
 * @param config The configuration context.
 * @param parser The parser structure to initialize.
 * @param argc Argument count from main().
 * @param argv Argument vector from main().
 * @return true if initialization succeeds, false otherwise.
 */
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

static bool parse_args_loop(int argc, char **argv,
    config_t *config, parser_t *parser)
{
    event_type_t type;

    for (; parser->index < argc; parser->index++) {
        type = event_type_from_string(argv[parser->index], EVENT_CLI_MAP,
            sizeof(EVENT_CLI_MAP) / sizeof(EVENT_CLI_MAP[0]));
        EMIT(config->dispatcher, type, parser);
        if (config->exit)
            return true;
        if (parser->error)
            console_log(LOG_ERROR, "Parse error: %s", parser->error_msg);
        if (parser->free)
            free(parser->error_msg);
        if (parser->error)
            return false;
    }
    return true;
}

/**
 * @brief Main entry point for command-line parsing.
 *
 * Iterates over argv, dispatches handlers, validates each arg,
 * and checks for missing required values at the end.
 *
 * @param argc Argument count from main().
 * @param argv Argument vector from main().
 * @param config The configuration structure to fill.
 * @return true if parsing succeeds, false otherwise.
 */
bool parse_args(int argc, char **argv, config_t *config)
{
    parser_t parser;

    if (!init_parser(config, &parser, argc, argv))
        return false;
    if (!parse_args_loop(argc, argv, config, &parser))
        return false;
    if (!check_unset_values(config, &parser)) {
        console_log(LOG_ERROR, "Parse error: %s, see -h", parser.error_msg);
        return false;
    }
    return true;
}
