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



static float get_delta_time(struct timeval *last_time)
{
    struct timeval now;
    float delta = 0.0f;

    gettimeofday(&now, NULL);
    delta = (float)(now.tv_sec - last_time->tv_sec)
        + (float)(now.tv_usec - last_time->tv_usec) / 1000000.0f;
    *last_time = now;
    return delta;
}

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
    self->command_manager->methods->process_all(self->command_manager, self,
        delta);
}

static void update_game(server_t *self)
{
    if (self->game && self->game->methods)
        self->game->methods->tick(self->game, get_ms_time());
    dispatch_game_events(self);
}

void run_server(server_t *self)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 0;
    struct timeval last_tick = {0};
    float delta;

    gettimeofday(&last_tick, NULL);
    memset(fds, 0, sizeof(fds));
    while (1) {
        if (!poll_clients(self, fds, &nfds))
            break;
        delta = get_delta_time(&last_tick);
        update_commands(self, delta);
        update_game(self);
    }
}
