/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** frequency_arg.c
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
 * @brief Validates the frequency argument in the parser context.
 *
 * Ensures frequency is not defined multiple times, is provided with a
 * value, and that the value is a valid float. Updates the parser's error
 * message on failure.
 *
 * @param config Pointer to the config being modified.
 * @param parser Pointer to the argument parser context.
 * @return true if the argument is valid, false otherwise.
 */
static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->frequency != -1.0f) {
        parser->error_msg = "Multiple frequency definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing frequency value";
        return false;
    }
    if (!config->methods->is_float(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid frequency format";
        return false;
    }
    return true;
}

/**
 * @brief Handler for the "-f" frequency argument.
 *
 * Parses and validates the frequency value from command-line args.
 * Stores the result in the config if valid. On failure, sets the
 * error flag and message in the parser.
 *
 * @param ctx Pointer to the config instance (cast from void).
 * @param data Pointer to the parser instance (cast from void).
 */
void frequency_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->frequency = atof(parser->argv[parser->index + 1]);
    if (config->frequency <= 0.0f) {
        parser->error_msg = "Frequency must be a positive number";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "Frequency set to %.2f", config->frequency);
}
