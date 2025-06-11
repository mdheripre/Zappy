/*
** EPITECH PROJECT, 2025
** server
** File description:
** server_run
*/


#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                                SERVER LOOP                               */
/*                                                                          */
/****************************************************************************/

static bool poll_clients(server_t *self, struct pollfd *fds, nfds_t *nfds)
{
    int ret = 0;

    self->vtable->setup_poll(self, fds, nfds);
    ret = poll(fds, *nfds, TIMEOUT_MS);
    if (ret < 0) {
        console_log(LOG_ERROR, "Poll failed: %s", strerror(errno));
        return false;
    }
    self->vtable->handle_poll(self, fds);
    return true;
}

static void update_commands(server_t *self, float delta)
{
    if (!self->command_manager)
        return;
    self->command_manager->methods->process_identify(self->command_manager,
        self);
    self->command_manager->methods->process_all(self->command_manager,
        self, delta);
}

static void update_game(server_t *self)
{
    if (!self || !self->game || !self->game->methods)
        return;
    self->game->methods->update(self->game);
    self->game->methods->dispatch_events(self->game);
    self->command_manager->methods->process_responses(self->command_manager,
        self->game);
}

static void on_tick(server_t *self, float delta, long *last_ms,
    long *current_ms)
{
    *last_ms = *current_ms;
    update_commands(self, delta);
    update_game(self);
}

void run_server(server_t *self)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 0;
    struct timeval last_tick = {0};
    long last_ms = 0;
    long current_ms = 0;
    long tick_interval = (long)(1000.0 / self->game->frequency);
    float delta = 1.0f;

    gettimeofday(&last_tick, NULL);
    last_ms = get_ms_time();
    memset(fds, 0, sizeof(fds));
    while (1) {
        if (!poll_clients(self, fds, &nfds))
            break;
        current_ms = get_ms_time();
        if ((current_ms - last_ms) >= tick_interval)
            on_tick(self, delta, &last_ms, &current_ms);
    }
}
