/*
** EPITECH PROJECT, 2025
** server
** File description:
** handle_poll
*/


#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                              POLLING SYSTEM                              */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Maps GUI command strings to corresponding event types.
 *
 * Used to trigger GUI events when matching commands are received.
 */
static const gui_command_event_t GUI_COMMAND_EVENTS[] = {
    {"Fork", EVENT_GUI_PFK},
    {"Forward", EVENT_GUI_PMV},
    {"Eject", EVENT_GUI_PEJ},
    {NULL, 0}
};

/**
 * @brief Immediately emits a GUI event based on command name.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client sending the command.
 * @param cmd_name Command name (e.g., "Fork").
 * @param clean Full command line with arguments.
 */
static void handle_gui_command(server_t *server, client_t *client,
    const char *cmd_name, const char *clean)
{
    char built[BUFFER_COMMAND_SIZE] = {0};
    event_type_t type;

    snprintf(built, sizeof(built), "command_gui_%s", cmd_name);
    console_log(LOG_INFO, "Executing GUI command immediately: %s", built);
    type = event_type_from_string(built,
        EVENT_CMD_NAME, sizeof(EVENT_CMD_NAME) / sizeof(EVENT_CMD_NAME[0]));
    client_enqueue_command(client, clean, 0, server->game);
    EMIT(server->command_manager->dispatcher, type, client);
    client_dequeue_command(client, NULL);
}

/**
 * @brief Emits a GUI event if the command matches a known GUI command.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client sending the command.
 * @param cmd_name Name of the command to check.
 */
void maybe_emit_gui_command_event(server_t *server,
    client_t *client, const char *cmd_name)
{
    for (int i = 0; GUI_COMMAND_EVENTS[i].name; i++) {
        if (strcmp(cmd_name, GUI_COMMAND_EVENTS[i].name) == 0) {
            EMIT(server->command_manager->dispatcher,
            GUI_COMMAND_EVENTS[i].event, client->player);
            return;
        }
    }
}

/**
 * @brief Handles a command by enqueuing it and possibly triggering an event.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client sending the command.
 * @param clean Full cleaned-up command string.
 * @param cmd_name Parsed name of the command.
 */
static void handle_command_enqueue(server_t *server, client_t *client,
    const char *clean, const char *cmd_name)
{
    int ticks = server->vtable->get_command_delay(server, clean);

    console_log(LOG_INFO, "handle poll: %s / current tick game %d", clean,
        server->game->tick_counter);
    if (client->type == CLIENT_IA && client->commands->size == 0)
        maybe_emit_gui_command_event(server, client, cmd_name);
    if (!client_enqueue_command(client, clean, ticks, server->game)) {
        console_log(LOG_WARNING,
            "Client %d: command queue full, dropped \"%s\"",
            client->fd, clean);
    }
}

/**
 * @brief Processes a complete command line from a client.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client sending the command.
 * @param line Null-terminated command string.
 */
void process_command_line(server_t *server, client_t *client, const char *line)
{
    char clean[BUFFER_COMMAND_SIZE] = {0};
    char cmd_name[BUFFER_CMD_NAME] = {0};

    if (!server || !client || !line)
        return;
    strncpy(clean, line, sizeof(clean) - 1);
    clean[sizeof(clean) - 1] = '\0';
    strip_linefeed(clean);
    extract_command_name(clean, cmd_name, sizeof(cmd_name));
    if (client->type == CLIENT_GUI)
        handle_gui_command(server, client, cmd_name, clean);
    else
        handle_command_enqueue(server, client, clean, cmd_name);
}

/**
 * @brief Extracts and processes all complete lines in a client's buffer.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client with data in its buffer.
 */
static void extract_commands_from_buffer(server_t *server,
    client_t *client)
{
    char *p = client->read_buffer;
    char *end = p + client->buffer_len;
    char *line_start = p;
    size_t remaining;

    while (p < end) {
        if (*p == '\n') {
            *p = '\0';
            process_command_line(server, client, line_start);
            line_start = p + 1;
        }
        ++p;
    }
    remaining = end - line_start;
    memmove(client->read_buffer, line_start, remaining);
    client->buffer_len = remaining;
}

/**
 * @brief Appends incoming data to the client's read buffer.
 *
 * @param client Pointer to the client instance.
 * @param buf Pointer to the data to append.
 * @param bytes Number of bytes to copy.
 */
static void append_to_read_buffer(client_t *client,
    const char *buf, ssize_t bytes)
{
    memcpy(client->read_buffer + client->buffer_len, buf, bytes);
    client->buffer_len += bytes;
    client->read_buffer[client->buffer_len] = '\0';
}

/**
 * @brief Handles possible read errors for a client socket.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client being read.
 * @param bytes Number of bytes returned by read().
 * @return 1 if client should be closed or ignored, 0 otherwise.
 */
static int handle_client_read_error(server_t *server, client_t *client,
    ssize_t bytes)
{
    if (bytes < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return 1;
        console_log(LOG_WARNING,
            "Client (fd=%d) read error: %s", client->fd, strerror(errno));
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PDI,
            client->player);
        server->vtable->remove_client(server, client);
        return 1;
    }
    if (bytes == 0) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PDI,
            client->player);
        server->vtable->remove_client(server, client);
        return 1;
    }
    return 0;
}

/**
 * @brief Reads data from a client socket and processes it.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client to read from.
 */
void read_from_client(server_t *server, client_t *client)
{
    char buf[BUFFER_COMMAND_SIZE] = {0};
    ssize_t bytes = 0;

    if (!server || !client)
        return;
    bytes = read(client->fd, buf, sizeof(buf));
    if (handle_client_read_error(server, client, bytes))
        return;
    if (client->buffer_len + bytes >= CLIENT_BUFFER_SIZE) {
        console_log(LOG_WARNING,
            "Buffer overflow for client %d", client->fd);
        dprintf(client->fd, "ko\n");
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PDI,
            client->player);
        server->vtable->remove_client(server, client);
        return;
    }
    append_to_read_buffer(client, buf, bytes);
    extract_commands_from_buffer(server, client);
}

/**
 * @brief Handles the result of a `poll()` on all server-related sockets.
 *
 * Accepts new clients and processes input from existing ones.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structures used in polling.
 */
void handle_server_poll(server_t *self, struct pollfd *fds)
{
    list_node_t *node = NULL;
    list_node_t *next = NULL;
    client_t *client = NULL;
    int poll_index = 1;

    if (fds[0].revents & POLLIN)
        self->vtable->accept_client(self);
    for (node = self->clients->head; node; poll_index++) {
        next = node->next;
        client = node->data;
        if (!client)
            continue;
        if (fds[poll_index].revents & (POLLIN | POLLHUP))
            read_from_client(self, client);
        node = next;
    }
}
