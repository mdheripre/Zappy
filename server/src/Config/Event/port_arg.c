/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** port_arg.c
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
 * check_errors - Validate the "-p" argument (server port).
 * Ensures the port is defined only once, followed by a valid integer.
 * Returns false and sets error message if the argument is invalid.
 *
 * @param config: The configuration structure being filled.
 * @param parser: The current parser state (argv, argc, index, etc).
 * @return true if valid, false otherwise.
 */
static bool check_errors(config_t *config, parser_t *parser)
{
    static bool initialized = false;

    if (initialized || config->port != -1) {
        parser->error_msg = "Multiple port definitions";
        return false;
    }
    initialized = true;
    if (parser->index + 1 >= parser->argc ||
        (parser->argv[parser->index + 1][0] == '-' &&
        isalpha(parser->argv[parser->index + 1][1]))) {
        parser->error_msg = "Missing port number";
        return false;
    }
    if (!config->methods->is_int(parser->argv[parser->index + 1])) {
        parser->error_msg = "Invalid port number format";
        return false;
    }
    return true;
}

/**
 * @brief Handles the "-p" argument to set the server port.
 *
 * Parses and validates the given port value from command-line arguments.
 * Accepts values from 1024 to 65535 (or 0 for random port). Reports
 * errors if the format is invalid or value is out of range.
 *
 * @param ctx Pointer to the config structure.
 * @param data Pointer to the parser structure.
 */
void port_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(config, parser)) {
        parser->error = true;
        return;
    }
    config->port = atoi(parser->argv[parser->index + 1]);
    if ((config->port < 1024 && config->port != 0) || config->port > 65535) {
        parser->error_msg = "Port number must be between 1024 and 65535";
        parser->error = true;
        return;
    }
    parser->index++;
    console_log(LOG_INFO, "Server port set to %d", config->port);
}
