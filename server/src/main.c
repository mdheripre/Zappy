/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** main
*/

#include "config.h"
#include "server.h"
#include "shared.h"

static void handle_sigint(int sig)
{
    (void)sig;
    DELETE();
    exit(0);
}

static int terminate(int return_value)
{
    DELETE();
    return return_value;
}

int main(int argc, char **argv)
{
    server_t *server;
    config_t *config = NEW(config);

    signal(SIGINT, handle_sigint);
    if (!config || !config->methods->parse_args(argc, argv, config))
        return terminate(84);
    if (config->exit)
        return terminate(0);
    server = NEW(server, config);
    if (!server)
        return terminate(84);
    server->vtable->run(server);
    return terminate(0);
}
