/*
** EPITECH PROJECT, 2025
** server
** File description:
** server_run
*/


#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                                SERVER LOOP                               */
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
 * @brief Get the minimum remaining ticks across all client commands.
 *
 * @param server Pointer to the server instance.
 * @return Minimum tick count among all queued commands.
 */
static int get_min_tick_from_commands(server_t *server)
{
    int min_tick = INT_MAX;
    client_t *c = NULL;
    queued_command_t *cmd = NULL;

    for (int i = 0; i < server->client_count; i++) {
        c = &server->clients[i];
        if (!c || !c->connected || c->type != CLIENT_IA || !c->commands)
            continue;
        cmd = c->commands->methods->front(c->commands);
        if (cmd && cmd->ticks_remaining < min_tick)
            min_tick = cmd->ticks_remaining;
    }
    return min_tick;
}

/**
 * @brief Compute remaining ticks before a player starts starving.
 *
 * @param p Pointer to the player.
 * @return Remaining ticks before food must be consumed.
 */
static int get_player_food_tick(player_t *p)
{
    if (!p || !p->is_alive)
        return INT_MAX;
    return 126 - p->nbr_tick;
}

/**
 * @brief Get the minimum food tick across all players.
 *
 * @param server Pointer to the server instance.
 * @param current_min Current minimum tick value to update.
 * @return Updated minimum tick value.
 */
static int get_min_tick_from_players(server_t *server, int current_min)
{
    player_t *p = NULL;
    int food_tick = 0;

    for (list_node_t *n = server->game->players->head; n; n = n->next) {
        p = n->data;
        food_tick = get_player_food_tick(p);
        if (food_tick < current_min)
            current_min = food_tick;
    }
    return current_min;
}

/**
 * @brief Get the minimum tick remaining from all ongoing incantations.
 *
 * @param game Pointer to the game instance.
 * @param current_min Current minimum tick value to update.
 * @return Updated minimum tick value.
 */
static int get_min_tick_from_incantations(game_t *game, int current_min)
{
    incantation_t *inc = NULL;

    for (list_node_t *n = game->incantations->head; n; n = n->next) {
        inc = n->data;
        if (inc && inc->tick_remaining < current_min)
            current_min = inc->tick_remaining;
    }
    return current_min;
}

/**
 * @brief Determine the next event to occur based on ticks.
 *
 * @param server Pointer to the server instance.
 * @return tick_info_t struct containing tick count and event name.
 */
static tick_info_t get_earliest_tick_event(server_t *server)
{
    tick_info_t result = { .ticks = INT_MAX, .origin = "NONE" };
    int tiled = 20 - server->game->tick_counter_tiled;
    int ticks[4] = {
        get_min_tick_from_commands(server),
        get_min_tick_from_players(server, result.ticks),
        tiled,
        get_min_tick_from_incantations(server->game, result.ticks)
    };

    for (int i = 0; i < 4; i++) {
        if (ticks[i] < result.ticks) {
            result.ticks = ticks[i];
            result.origin = TICK_EVENT_NAMES[i];
        }
    }
    return result;
}

/**
 * @brief Compute timeout (in ms) until the next server event.
 *
 * @param server Pointer to the server instance.
 * @return Timeout in milliseconds, or -1 if no event is scheduled.
 */
static int compute_next_event_timeout_ms(server_t *server)
{
    tick_info_t info = get_earliest_tick_event(server);
    int timeout = 0;

    if (info.ticks == INT_MAX)
        return -1;
    timeout = (int)(roundf(1000.0f * (info.ticks / server->game->frequency)));
    console_log(LOG_INFO, "Next event: %s in %d ticks -> timeout: %d ms",
        info.origin, info.ticks, timeout);
    return timeout;
}

/**
 * @brief Perform polling on client sockets with computed timeout.
 *
 * @param server Pointer to the server instance.
 * @param fds Array of pollfd structures.
 * @param nfds Pointer to number of file descriptors.
 * @param timeout Poll timeout in milliseconds.
 * @return true on success, false on error.
 */
static bool poll_clients(server_t *server, struct pollfd *fds, nfds_t *nfds,
    int timeout)
{
    int ret = 0;

    server->vtable->setup_poll(server, fds, nfds);
    ret = poll(fds, *nfds, timeout);
    if (ret < 0) {
        console_log(LOG_ERROR, "Poll failed: %s", strerror(errno));
        return false;
    }
    server->vtable->handle_poll(server, fds);
    return true;
}

/**
 * @brief Apply a tick update to the game state.
 *
 * Updates commands, players, events, and responses.
 *
 * @param server Pointer to the server instance.
 * @param tick_count Number of ticks to apply.
 */
static void on_tick(server_t *server, int tick_count)
{
    if (tick_count <= 0)
        return;
    server->game->tick_counter += tick_count;
    console_log(LOG_INFO, "Tick applied: +%d -> current tick game = %ld",
        tick_count, server->game->tick_counter);
    server->command_manager->methods->process_all(server->command_manager,
        server, tick_count);
    server->game->methods->update(server->game, tick_count);
    server->game->methods->dispatch_events(server->game);
    server->command_manager->methods->process_responses(
        server->command_manager, server->game);
}

/**
 * @brief Update the tick if time has passed since the last tick.
 *
 * @param server Pointer to the server instance.
 * @param now Current timestamp in milliseconds.
 * @param last_ms Pointer to last tick timestamp.
 */
static void update_tick_if_needed(server_t *server, long now, long *last_ms)
{
    long elapsed_ms = now - *last_ms;
    int tick_count = 0;

    if (elapsed_ms <= 0)
        return;
    tick_count = (int)floorf((elapsed_ms / 1000.0f) * server->game->frequency);
    if (tick_count > 0) {
        on_tick(server, tick_count);
        *last_ms = now;
    }
}

/**
 * @brief Main loop of the server. Manages polling, tick updates and events.
 *
 * @param server Pointer to the server instance.
 */
void run_server(server_t *server)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 0;
    long last_ms = get_ms_time();
    long now = 0;
    int timeout = 0;

    while (true) {
        timeout = compute_next_event_timeout_ms(server);
        memset(fds, 0, sizeof(fds));
        if (!poll_clients(server, fds, &nfds, timeout))
            break;
        now = get_ms_time();
        server->command_manager->methods->process_identify(
            server->command_manager, server);
        update_tick_if_needed(server, now, &last_ms);
    }
}
