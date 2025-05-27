/*
** EPITECH PROJECT, 2025
** server
** File description:
** server_run
*/


#include "server.h"
#include "utils.h"

float get_delta_time(struct timeval *last_time)
{
    struct timeval now;
    float delta = 0.0f;

    gettimeofday(&now, NULL);
    delta = (float)(now.tv_sec - last_time->tv_sec)
        + (float)(now.tv_usec - last_time->tv_usec) / 1000000.0f;
    *last_time = now;
    return delta;
}

void run_server(server_t *self)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 0;
    int ret;
    struct timeval last_tick = {0};
    float delta;

    gettimeofday(&last_tick, NULL);
    memset(fds, 0, sizeof(fds));
    while (1) {
        self->vtable->setup_poll(self, fds, &nfds);
        ret = poll(fds, nfds, TIMEOUT_MS);
        if (ret < 0) {
            console_log(LOG_ERROR, "Poll failed: %s", strerror(errno));
            break;
        }
        self->vtable->handle_poll(self, fds);
        delta = get_delta_time(&last_tick);
        command_process_identify(self);
        command_process_all(self, delta);
    }
}
