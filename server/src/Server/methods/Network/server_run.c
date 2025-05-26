/*
** EPITECH PROJECT, 2025
** server
** File description:
** server_run
*/


#include "server.h"
#include "utils.h"

void run_server(server_t *self)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 0;
    int ret;

    console_log(LOG_INFO, "Starting server loop");
    while (1) {
        self->vtable->setup_poll(self, fds, &nfds);
        ret = poll(fds, nfds, TIMEOUT_MS);
        if (ret < 0) {
            console_log(LOG_ERROR, "Poll failed: %s", strerror(errno));
            break;
        }
        self->vtable->handle_poll(self, fds);
    }
}
