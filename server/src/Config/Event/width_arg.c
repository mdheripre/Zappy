/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** width.c
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
 * check_errors - Validate the width argument from the command line.
 * Ensures that the width is only set once and that the provided
 * argument exists and is a valid integer.
 *
 * @param config: Pointer to the config structure being filled.
 * @param parser: Pointer to the parser containing arguments and state.
 * @return true if the width argument is valid and unique, false otherwise.
 */
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

/**
 * @brief Handles the "-x" argument to set world width.
 *
 * Parses the width value from command-line input and stores
 * it in the configuration. The value must be strictly positive.
 *
 * @param ctx Pointer to the config structure.
 * @param data Pointer to the parser structure.
 */
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
