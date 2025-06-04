/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** team_name_arg.c
*/

#include "config.h"
#include "utils.h"

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

static bool add_team(config_t *config, parser_t *parser)
{
    char *team_name = NULL;

    if (config->team_name->methods->contain(config->team_name,
        parser->argv[parser->index + 1], config->methods->str_are_equals)) {
        parser->error_msg = "Duplicate team name";
        return false;
    }
    if (parser->argv[parser->index + 1][0] == '\0') {
        parser->error_msg = "Team name cannot be empty";
        return false;
    }
    team_name = strdup(parser->argv[parser->index + 1]);
    if (!team_name) {
        parser->error_msg = "Failed to allocate memory for team name";
        return false;
    }
    config->team_name->methods->push_back(config->team_name, team_name);
    console_log(LOG_INFO, "Team name added: %s", team_name);
    return true;
}

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
