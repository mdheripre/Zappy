/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** team_size_arg.c
*/

#include "config.h"
#include "utils.h"
#include <ctype.h>

/****************************************************************************/
/*                                                                          */
/*                              EVENTS FLAGS                                */
/*                                                                          */
/****************************************************************************/

/**
 * check_errors - Validate the team size argument from the command line.
 * Ensures that the team size is defined only once and that the provided
 * argument exists and is a valid integer.
 *
 * @param config: The configuration object being filled.
 * @param parser: The current parser state, including arguments and index.
 * @return true if the team size argument is valid and unique, false otherwise.
 */
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

/**
 * @brief Handles the "-c" argument to set team size.
 *
 * Parses and sets the maximum number of players allowed per team.
 * The value must be a positive integer. Errors are reported via parser.
 *
 * @param ctx Pointer to the config structure.
 * @param data Pointer to the parser structure.
 */
void team_size_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->team_size = atoi(parser->argv[parser->index + 1]);
    if (config->team_size < 1 || config->team_size > 200) {
        parser->error_msg = "Team size must be between 1 and 200";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "Team size set to %d", config->team_size);
}
