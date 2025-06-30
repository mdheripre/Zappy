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
 * @brief Enqueue a new command into the client's command queue.
 *
 * Initializes a queued_command_t with delay, content, and tick metadata.
 * Logs the reception and scheduling details.
 *
 * @param client Pointer to the client.
 * @param cmd Command string to enqueue.
 * @param ticks Number of ticks before execution.
 * @param game Pointer to the game instance (for current tick counter).
 * @return true if the command was enqueued successfully, false otherwise.
 */
bool client_enqueue_command(client_t *client, const char *cmd, int ticks,
    game_t *game)
{
    queued_command_t *entry = NULL;

    if (!client || !cmd || !client->commands ||
        client->commands->size >= MAX_COMMANDS)
        return false;
    entry = malloc(sizeof(queued_command_t));
    if (!entry)
        return false;
    memset(entry, 0, sizeof(queued_command_t));
    strncpy(entry->content, cmd, CLIENT_BUFFER_SIZE - 1);
    entry->content[CLIENT_BUFFER_SIZE - 1] = '\0';
    entry->ticks_remaining = ticks;
    entry->gui_check = GUI_CMD_NONE;
    entry->last_tick_checked = (ticks > 0) ? game->tick_counter + 1 :
        game->tick_counter;
    console_log(LOG_SUCCESS, "Command \"%s\" received, receive at tick %d,\n"
        "  start decrementing at tick %d", entry->content, game->tick_counter,
        entry->last_tick_checked);
    client->commands->methods->push_back(client->commands, entry);
    return true;
}

/**
 * @brief Add a command to the front of the client's command queue.
 *
 * This function allows you to add a command that should be executed
 * immediately or with a specified delay, placing it at the front of the queue.
 *
 * @param client Pointer to the client.
 * @param cmd Command string to enqueue.
 * @param delay Time before the command is executed.
 * @return true on success, false on failure.
 */
bool client_enqueue_front_command(client_t *client, const char *cmd,
    float delay)
{
    queued_command_t *entry = NULL;

    if (!client || !cmd || !client->commands)
        return false;
    entry = malloc(sizeof(queued_command_t));
    if (!entry)
        return false;
    memset(entry, 0, sizeof(queued_command_t));
    strncpy(entry->content, cmd, CLIENT_BUFFER_SIZE - 1);
    entry->content[CLIENT_BUFFER_SIZE - 1] = '\0';
    entry->ticks_remaining = delay;
    client->commands->methods->push_front(client->commands, entry);
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
