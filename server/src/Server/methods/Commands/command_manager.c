/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager
*/

#include "server.h"
#include "dispatcher.h"
#include "shared.h"
#include "utils.h"


void command_manager_register_all(server_t *server)
{
    REGISTER(server->dispatcher, "command_ia_Forward",
        handle_command_forward, NULL);
}

static void build_full_command(char *dest,
    size_t size, client_type_t type, const char *cmd)
{
    const char *prefix = (type == CLIENT_GUI) ? "gui" : "ia";

    snprintf(dest, size, "command_%s_%s", prefix, cmd);
    dest[size - 1] = '\0';
}

void command_process_identify(server_t *server)
{
    client_t *client = NULL;
    queued_command_t *cmd = NULL;
    int i = 0;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client->connected || client->type != CLIENT_UNDEFINED)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        EMIT(server->dispatcher, "client_identify", client);
    }
}

static void execute_command_if_ready(server_t *server,
    client_t *client, queued_command_t *cmd, float delta)
{
    char built[BUFFER_COMMAND_SIZE] = {0};

    cmd->time_remaining -= delta;
    console_log(LOG_INFO, "Client %d command: \"%s\" (%.2fs left)",
    client->fd, cmd->content, cmd->time_remaining);
    if (cmd->time_remaining > 0.0f)
        return;
    build_full_command(built, sizeof(built), client->type, cmd->content);
    EMIT(server->dispatcher, built, client);
    client_dequeue_command(client, NULL);
}

void command_process_all(server_t *server, float delta)
{
    int i = 0;
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client || !client->connected)
            continue;
        if (client->type != CLIENT_IA)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        execute_command_if_ready(server, client, cmd, delta);
    }
}
