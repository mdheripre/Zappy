/*
** EPITECH PROJECT, 2025
** server
** File description:
** handle_queu
*/


#include "server.h"
#include "client.h"

/****************************************************************************/
/*                                                                          */
/*                               QUEU SYSTEM                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Enqueues a command into the client's command queue.
 *
 * This function adds a command to the client's command queue with a specified
 * delay. If the queue is full, it returns false.
 *
 * @param client Pointer to the client structure.
 * @param cmd Command string to enqueue.
 * @param delay Delay in seconds before the command should be executed.
 * @return true if the command was successfully enqueued, false otherwise.
 */
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

/**
 * @brief Dequeues a command from the client's command queue.
 *
 * This function removes the next command from the client's command queue
 * and returns it through the out parameter. If the queue is empty, it returns
 * false.
 *
 * @param client Pointer to the client structure.
 * @param out Pointer to a queued_command_t structure to store the dequeued
 * command.
 * @return true if a command was successfully dequeued, false if the queue is
 * empty.
 */
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

/**
 * @brief Peeks at the next command in the client's command queue without
 * removing it.
 *
 * This function returns a pointer to the next command in the queue.
 * If the queue is empty, it returns NULL.
 *
 * @param client Pointer to the client structure.
 * @return Pointer to the next queued_command_t, or NULL if the queue is empty.
 */
queued_command_t *client_peek_command(client_t *client)
{
    if (!client || client->command_count == 0)
        return NULL;
    return &client->commands[client->command_head];
}
