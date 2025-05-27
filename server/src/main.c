/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** main
*/

#include "server.h"
#include "shared.h"

static void handle_sigint(int sig)
{
    (void)sig;
    DELETE();
    exit(0);
}

int main(void)
{
    server_t *server = NEW(server, 1234);

    signal(SIGINT, handle_sigint);
    if (!server)
        return 84;
    server->vtable->run(server);
    DELETE();
    return 0;
}
