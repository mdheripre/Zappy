/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** get_next_tick
*/

#include "server.h"
#include "game.h"
#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                            TIME MANAGEMENT                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Names of tick event sources used for logging and tracking.
 */
static const char *TICK_EVENT_NAMES[4] = {
    "COMMAND",
    "FOOD",
    "TILE_UPDATED",
    "INCANTATION"
};

/**
 * @brief Compute remaining ticks before the first command is ready.
 *
 * Uses the current game tick and the command's last checked tick.
 *
 * @param self Pointer to the server instance.
 * @param cli Pointer to the client.
 * @return Ticks remaining, or INT_MAX if invalid or no command.
 */
static int get_ticks_remaining_command(server_t *self, client_t *cli)
{
    queued_command_t *cmd = NULL;
    int delta = 0;
    int left = 0;

    if (!cli || !cli->connected || cli->type != CLIENT_IA || !cli->commands)
        return INT_MAX;
    cmd = cli->commands->methods->front(cli->commands);
    if (!cmd)
        return INT_MAX;
    delta = self->game->tick_counter - cmd->last_tick_checked;
    left = cmd->ticks_remaining - delta;
    return (left < 0) ? 0 : left;
}

/**
 * @brief Get the minimum ticks remaining among all clients' commands.
 *
 * @param self Pointer to the server instance.
 * @return Minimum ticks remaining, or INT_MAX if none.
 */
static int get_min_command_ticks(server_t *self)
{
    int min = INT_MAX;
    int remain = 0;

    for (int i = 0; i < self->client_count; ++i) {
        remain = get_ticks_remaining_command(self, &self->clients[i]);
        if (remain < min)
            min = remain;
    }
    return min;
}

/**
 * @brief Compute how many ticks a player has before starving.
 *
 * @param p Pointer to the player.
 * @return Remaining food ticks, or INT_MAX if player is invalid or dead.
 */
static int get_player_food_ticks(player_t *p)
{
    if (!p || !p->is_alive)
        return INT_MAX;
    return 126 - p->nbr_tick;
}

/**
 * @brief Get the lowest food countdown among all players.
 *
 * @param self Pointer to the server instance.
 * @return Minimum food ticks remaining, or INT_MAX if none.
 */
static int get_min_food_ticks(server_t *self)
{
    int min = INT_MAX;
    list_node_t *node = self->game->players->head;
    player_t *p = NULL;
    int ticks = 0;

    while (node) {
        p = node->data;
        ticks = get_player_food_ticks(p);
        if (ticks < min)
            min = ticks;
        node = node->next;
    }
    return min;
}

/**
 * @brief Get the minimum ticks remaining for all incantations.
 *
 * @param game Pointer to the game instance.
 * @return Minimum tick count before next incantation ends, or INT_MAX.
 */
static int get_min_incant_ticks(game_t *game)
{
    int min = INT_MAX;
    list_node_t *n = game->incantations->head;
    incantation_t *i = NULL;

    while (n) {
        i = n->data;
        if (i && i->tick_remaining < min)
            min = i->tick_remaining;
        n = n->next;
    }
    return min;
}

/**
 * @brief Determine the next scheduled tick-based event in the game.
 *
 * Checks command, food, tile update, and incantation events.
 *
 * @param self Pointer to the server instance.
 * @return tick_info_t structure with tick count and event origin name.
 */
tick_info_t get_next_tick_info(server_t *self)
{
    tick_info_t info = { .ticks = INT_MAX, .origin = "NONE" };
    int tick_list[4] = {
        get_min_command_ticks(self),
        get_min_food_ticks(self),
        20 - self->game->tick_counter_tiled,
        get_min_incant_ticks(self->game)
    };

    for (int i = 0; i < 4; i++) {
        if (tick_list[i] < info.ticks) {
            info.ticks = tick_list[i];
            info.origin = TICK_EVENT_NAMES[i];
        }
    }
    return info;
}
