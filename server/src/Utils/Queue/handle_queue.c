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
 * @brief Add a command to the client's command queue.
 *
 * @param client Pointer to the client.
 * @param cmd Command string to enqueue.
 * @param delay Time before the command is executed.
 * @return true on success, false on failure.
 */
bool client_enqueue_command(client_t *client, const char *cmd, float delay)
{
    queued_command_t *entry = NULL;

    if (!client || !cmd || !client->commands ||
        client->commands->size >= MAX_COMMANDS)
        return false;
    entry = malloc(sizeof(queued_command_t));
    if (!entry)
        return false;
    memset(entry, 0, sizeof(queued_command_t));
    strncpy(entry->content, cmd, BUFFER_COMMAND_SIZE - 1);
    entry->content[BUFFER_COMMAND_SIZE - 1] = '\0';
    entry->time_remaining = delay;
    client->commands->methods->push_back(client->commands, entry);
    return true;
}

/**
 * @brief Remove and return the next command from the queue.
 *
 * @param client Pointer to the client.
 * @param out Optional output to receive the command data.
 * @return true on success, false if the queue is empty or invalid.
 */
bool client_dequeue_command(client_t *client, queued_command_t *out)
{
    queued_command_t *entry = NULL;

    if (!client || !client->commands || client->commands->size == 0)
        return false;
    entry = client->commands->methods->pop_front(client->commands);
    if (!entry)
        return false;
    if (out)
        memcpy(out, entry, sizeof(queued_command_t));
    free(entry);
    return true;
}

/**
 * @brief Return the command at the front of the client's queue.
 *
 * @param client Pointer to the client.
 * @return Pointer to the queued command, or NULL if the queue is empty.
 */
queued_command_t *client_peek_command(client_t *client)
{
    if (!client || !client->commands || client->commands->size == 0)
        return NULL;
    return (queued_command_t *)client->commands->head->data;
}
