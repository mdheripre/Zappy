/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** height_arg.c
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
 * @brief Validates the height argument in the parser context.
 *
 * Ensures height is not already defined, that a value follows the flag,
 * and that the value is a valid integer. If not, sets an error message
 * in the parser.
 *
 * @param config Pointer to the configuration being modified.
 * @param parser Pointer to the parser context.
 * @return true if the height argument is valid, false otherwise.
 */
static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->height != -1) {
        parser->error_msg = "Multiple height definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing height value";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid height format";
        return false;
    }
    return true;
}

/**
 * @brief Handler for the "-y" height argument.
 *
 * Parses the height value from the command-line and updates the config.
 * Triggers an error in the parser if the value is missing or invalid.
 *
 * @param ctx Pointer to the config instance (cast from void).
 * @param data Pointer to the parser instance (cast from void).
 */
void height_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->height = atoi(parser->argv[parser->index + 1]);
    if (config->height < 10 || config->height > 42) {
        parser->error_msg = "Height must be between 10 and 42";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "World height set to %d", config->height);
}
