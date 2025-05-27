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

static bool queue_command(client_t *client, const char *full_cmd, float delay)
{
    int tail = client->command_tail;
    queued_command_t *slot = &client->commands[tail];

    memset(slot, 0, sizeof(queued_command_t));
    strncpy(slot->content, full_cmd, BUFFER_COMMAND_SIZE - 1);
    slot->content[BUFFER_COMMAND_SIZE - 1] = '\0';
    slot->time_remaining = delay;
    client->command_tail = (tail + 1) % MAX_COMMANDS;
    client->command_count++;
    return true;
}

void command_manager_handle(server_t *server,
    client_t *client, const char *command)
{
    char full_command[BUFFER_COMMAND_SIZE] = {0};
    float delay = 0.0f;

    if (!server || !client || !command)
        return;
    if (client->command_count >= MAX_COMMANDS) {
        write(client->fd, "ko\n", 3);
        return;
    }
    build_full_command(full_command,
        sizeof(full_command), client->type, command);
    delay = server->vtable->get_command_delay(server, command);
    queue_command(client, full_command, delay);
}

void command_process_all(server_t *server)
{
    client_t *client = NULL;
    int i = 0;
    int pos = 0;
    int index = 0;
    queued_command_t *cmd;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client->connected || client->command_count == 0)
            continue;
        console_log(LOG_INFO, "Client %d has %d command(s):",
            client->fd, client->command_count);
        pos = client->command_head;
        for (index = 0; index < client->command_count; index++) {
            cmd = &client->commands[pos];
            console_log(LOG_INFO, " -> [%d] \"%s\" (%.2fs)",
                index, cmd->content, cmd->time_remaining);
            pos = (pos + 1) % MAX_COMMANDS;
        }
    }
}
