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
/*                            TIME MANAGEMENT                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Update the server's internal timer based on current time.
 *
 * Computes the elapsed time since the last tick and accumulates it.
 *
 * @param self Pointer to the server instance.
 */
static void update_time(server_t *self)
{
    long now = get_ms_time();

    self->accumulated_ms += (float)(now - self->last_tick_time);
    self->last_tick_time = now;
}

/**
 * @brief Apply accumulated ticks based on elapsed milliseconds.
 *
 * Increments the game tick counter accordingly and logs the update.
 *
 * @param self Pointer to the server instance.
 * @return Number of ticks applied.
 */
static int apply_ticks(server_t *self)
{
    float ms_tick = 1000.0f / self->game->frequency;
    int to_apply = (int)(self->accumulated_ms / ms_tick);
    long from = self->game->tick_counter;

    if (to_apply <= 0)
        return 0;
    self->accumulated_ms -= to_apply * ms_tick;
    self->game->tick_counter += to_apply;
    console_log(LOG_INFO,
        "Current tick game: %ld (applied +%d, from tick %ld to %ld)",
        self->game->tick_counter, to_apply, from, self->game->tick_counter);
    return to_apply;
}

/**
 * @brief Compute the timeout in milliseconds until the next event.
 *
 * Considers the game's frequency and the next scheduled tick.
 *
 * @param self Pointer to the server instance.
 * @return Timeout in milliseconds.
 */
static int compute_timeout(server_t *self)
{
    tick_info_t next = get_next_tick_info(self);
    float ms_tick = 1000.0f / self->game->frequency;
    int timeout = (int)(next.ticks * ms_tick - self->accumulated_ms);
    int ticks_shown = 0;

    if (next.ticks == 0 && self->accumulated_ms < ms_tick)
        timeout = (int)(ms_tick - self->accumulated_ms);
    if (timeout < 0)
        timeout = 0;
    ticks_shown = (int)(timeout / ms_tick);
    console_log(LOG_INFO,
        "Next event: %s in %d ticks -> timeout: %d ms",
        next.origin, ticks_shown, timeout);
    return timeout;
}

/****************************************************************************/
/*                                                                          */
/*                                ON TICK                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Update the game state if at least one tick has passed.
 *
 * Applies game updates, processes commands and responses,
 * and checks if the game has finished.
 *
 * @param self Pointer to the server instance.
 * @param ticks Number of ticks to apply.
 * @return true if the game has ended, false otherwise.
 */
static bool update_game_if_needed(server_t *self, int ticks)
{
    if (ticks <= 0)
        return false;
    self->game->methods->update(self->game, ticks);
    self->command_manager->methods->process_all(
        self->command_manager, self, self->game->tick_counter);
    self->game->methods->dispatch_events(self->game);
    self->command_manager->methods->process_responses(
        self->command_manager, self->game);
    if (self->game->methods->has_finished(self->game)) {
        EMIT(self->command_manager->dispatcher, "gui_seg", NULL);
        return true;
    }
    return false;
}

/****************************************************************************/
/*                                                                          */
/*                           POLLING SYSTEM                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Poll all client sockets for activity.
 *
 * Sets up poll descriptors and waits for events or timeout.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structs to populate.
 * @param nfds Pointer to the number of descriptors.
 * @param timeout Timeout in milliseconds.
 * @return true on success, false on poll failure.
 */
static bool poll_clients(server_t *self,
    struct pollfd *fds, nfds_t *nfds, int timeout)
{
    int ret = 0;

    if (!self || !fds || !nfds)
        return false;
    self->vtable->setup_poll(self, fds, nfds);
    ret = poll(fds, *nfds, timeout);
    if (ret < 0) {
        console_log(LOG_ERROR, "Poll failed: %s", strerror(errno));
        return false;
    }
    return true;
}

/**
 * @brief Handle input/output after polling clients.
 *
 * Processes socket events and identifies any unknown clients.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structs.
 */
static void handle_after_poll(server_t *self, struct pollfd *fds)
{
    self->vtable->handle_poll(self, fds);
    self->command_manager->methods->process_identify(
        self->command_manager, self);
}

/****************************************************************************/
/*                                                                          */
/*                              MAIN LOOP                                   */
/*                                                                          */
/****************************************************************************/

static struct pollfd *get_dynamic_pollfds(server_t *server, nfds_t *nfds)
{
    static struct pollfd *fds = NULL;
    struct pollfd *new_fds = NULL;
    static size_t capacity = 0;
    size_t required = 0;

    required = server->game->max_players + 1;
    if (capacity >= required) {
        *nfds = required;
        return fds;
    }
    new_fds = calloc(required, sizeof(struct pollfd));
    if (!new_fds)
        return NULL;
    gc_unregister(fds);
    free(fds);
    gc_register(new_fds, NULL);
    fds = new_fds;
    capacity = required;
    *nfds = required;
    return fds;
}

static void server_main_loop(server_t *self)
{
    nfds_t nfds = 0;
    struct pollfd *fds = NULL;
    int ticks_applied = 0;
    int timeout = 0;

    while (true) {
        fds = get_dynamic_pollfds(self, &nfds);
        if (!fds)
            break;
        update_time(self);
        ticks_applied = apply_ticks(self);
        timeout = compute_timeout(self);
        if (!poll_clients(self, fds, &nfds, timeout))
            break;
        update_time(self);
        ticks_applied += apply_ticks(self);
        handle_after_poll(self, fds);
        if (update_game_if_needed(self, ticks_applied))
            break;
    }
}

void run_server(server_t *self)
{
    self->last_tick_time = get_ms_time();
    self->accumulated_ms = 0.0f;
    server_main_loop(self);
}
