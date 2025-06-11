/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** team_name_arg.c
*/

#include "config.h"
#include "utils.h"
#include <string.h>

/****************************************************************************/
/*                                                                          */
/*                              EVENTS FLAGS                                */
/*                                                                          */
/****************************************************************************/

/**
 * check_errors - Validate the next argument as a team name.
 * Ensures there is a non-empty value that is not a new flag.
 *
 * @param parser: The current parser state.
 * @return true if valid team name is provided, false otherwise.
 */
static bool check_errors(parser_t *parser)
{
    if (parser->index + 1 >= parser->argc ||
        parser->argv[parser->index + 1][0] == '-' ||
        parser->argv[parser->index + 1][0] == '\0') {
        parser->error_msg = "Missing team name";
        return false;
    }
    return true;
}

/**
 * check_name - Validate the team name for uniqueness and non-empty value.
 * Checks if the name already exists in the config's team list and
 * ensures it is not empty or reserved.
 *
 * @param config: The configuration structure.
 * @param parser: The current parser state.
 * @param name: The team name to validate.
 * @return true if the name is valid, false otherwise.
 */
static bool check_name(config_t *config, parser_t *parser, char *name)
{
    if (config->team_name->methods->contain(config->team_name,
        name, config->methods->str_are_equals)) {
        parser->error_msg = "Duplicate team name";
        return false;
    }
    if (name[0] == '\0') {
        parser->error_msg = "Team name cannot be empty";
        return false;
    }
    if (strcmp(name, "GRAPHIC") == 0) {
        parser->error_msg = "Team name cannot be 'GRAPHIC' (reserved for GUI)";
        return false;
    }
    return true;
}

/**
 * add_team - Add a new team name to the config structure.
 * Verifies uniqueness, allocates memory, and stores the team name.
 * Logs success or sets an error message on failure.
 *
 * @param config: The configuration structure.
 * @param parser: The current parser state.
 * @return true if the team was added successfully, false otherwise.
 */
static bool add_team(config_t *config, parser_t *parser)
{
    char *team_name = NULL;

    if (!check_name(config, parser, parser->argv[parser->index + 1]))
        return false;
    team_name = strdup(parser->argv[parser->index + 1]);
    if (!team_name) {
        parser->error_msg = "Failed to allocate memory for team name";
        return false;
    }
    config->team_name->methods->push_back(config->team_name, team_name);
    console_log(LOG_INFO, "Team name added: %s", team_name);
    return true;
}

/**
 * @brief Handles the "-n" argument to add team names.
 *
 * Reads one or more team names from command-line arguments.
 * Verifies uniqueness and non-empty values. Stores each team
 * name in the config's team list.
 *
 * @param ctx Pointer to the config structure.
 * @param data Pointer to the parser structure.
 */
void team_name_arg(void *ctx, void *data)
{
    config_t *config = ctx;
    parser_t *parser = data;

    if (!check_errors(parser)) {
        parser->error = true;
        return;
    }
    for (; parser->index + 1 < parser->argc &&
        parser->argv[parser->index + 1][0] != '-'; parser->index++) {
        if (!add_team(config, parser)) {
            parser->error = true;
            return;
        }
    }
}
