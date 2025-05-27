/*
** EPITECH PROJECT, 2025
** server
** File description:
** handle_queu
*/


#include "server.h"
#include "client.h"

bool client_enqueue_command(client_t *client,
    const char *cmd, float delay)
{
    int next_tail = (client->command_tail + 1) % MAX_COMMANDS;
    queued_command_t *slot = NULL;

    if (!client || !cmd)
        return false;
    if (next_tail == client->command_head)
        return false;
    slot = &client->commands[client->command_tail];
    memset(slot, 0, sizeof(queued_command_t));
    strncpy(slot->content, cmd, BUFFER_COMMAND_SIZE - 1);
    slot->time_remaining = delay;
    client->command_tail = next_tail;
    client->command_count++;
    return true;
}

bool client_dequeue_command(client_t *client, queued_command_t *out)
{
    if (!client || client->command_count == 0)
        return false;
    if (out)
        *out = client->commands[client->command_head];
    client->command_head =
        (client->command_head + 1) % MAX_COMMANDS;
    client->command_count--;
    return true;
}

queued_command_t *client_peek_command(client_t *client)
{
    if (!client || client->command_count == 0)
        return NULL;
    return &client->commands[client->command_head];
}
