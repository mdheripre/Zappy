/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager
*/

#include "server.h"
#include "dispatcher.h"
#include "shared.h"


void command_manager_register_all(server_t *server)
{
    REGISTER(server->dispatcher, "command_forward",
        handle_command_forward, NULL);
}

void command_manager_handle(server_t *server, client_t *client,
    const char *command)
{
    char event_name[BUFFER_COMMAND_SIZE] = {0};

    COMMAND(event_name, command);
    EMIT(server->dispatcher, event_name, client);
}
