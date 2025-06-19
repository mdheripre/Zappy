/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** get_winner
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"


/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

static int find_team_index(char *team_names[], int team_size,
    char *team_name)
{
    for (int i = 0; i < team_size; i++) {
        if (strcmp(team_names[i], team_name) == 0)
            return i;
    }
    return -1;
}

static void add_team_if_needed(char *team_names[], int *team_size,
    char *team_name)
{
    int idx = find_team_index(team_names, *team_size, team_name);

    if (idx == -1 && *team_size < 100) {
        idx = (*team_size);
        (*team_size)++;
        team_names[idx] = team_name;
    }
}

static void count_players(game_t *self, char *team_names[],
    int team_counts[][9], int *team_size)
{
    player_t *p = NULL;
    int idx;

    for (list_node_t *node = self->players->head; node; node = node->next) {
        p = node->data;
        if (!p || !p->is_alive)
            continue;
        add_team_if_needed(team_names, team_size, p->team_name);
        idx = find_team_index(team_names, *team_size, p->team_name);
        if (p->level >= 1 && p->level <= 8)
            team_counts[idx][p->level]++;
    }
}

static char *direct_win(char *team_names[], int team_counts[][9],
    int team_size)
{
    for (int i = 0; i < team_size; i++) {
        if (team_counts[i][8] >= 6)
            return team_names[i];
    }
    return NULL;
}

static bool is_better_team(int team_score[9], int best_score[9])
{
    int diff;

    for (int lvl = 8; lvl >= 1; lvl--) {
        diff = team_score[lvl] - best_score[lvl];
        if (diff != 0)
            return diff > 0 ? true : false;
    }
    return false;
}

static bool is_equal_team(int team_score[9], int best_score[9])
{
    for (int lvl = 8; lvl >= 1; lvl--) {
        if (team_score[lvl] != best_score[lvl])
            return false;
    }
    return true;
}

static char *get_lexico_winner(char *team_names[],
    int team_counts[][9], int team_size)
{
    char *best_team = NULL;
    int best_score[9] = {0};
    bool tied = false;

    for (int i = 0; i < team_size; i++) {
        if (is_better_team(team_counts[i], best_score)) {
            memcpy(best_score, team_counts[i], sizeof(best_score));
            best_team = team_names[i];
            tied = false;
        }
        if (is_equal_team(team_counts[i], best_score) &&
            team_names[i] != best_team) {
            tied = true;
        }
    }
    return tied ? NULL : best_team;
}

char *get_winner(game_t *self)
{
    int max_teams = 100;
    int max_level = 8;
    char *team_names[max_teams];
    int team_counts[max_teams][max_level + 1];
    int team_size = 0;
    char *winner;

    memset(team_counts, 0, sizeof(team_counts));
    count_players(self, team_names, team_counts, &team_size);
    winner = direct_win(team_names, team_counts, team_size);
    if (winner)
        return winner;
    return get_lexico_winner(team_names, team_counts, team_size);
}
