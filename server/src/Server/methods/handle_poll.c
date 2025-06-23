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

static void maybe_emit_gui_command_event(server_t *server,
    client_t *client, const char *cmd_name)
{
    if (strcmp(cmd_name, "Fork") == 0)
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PFK,
            client->player);
    else if (strcmp(cmd_name, "Forward") == 0)
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PMV,
            client->player);
    else if (strcmp(cmd_name, "Eject") == 0)
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PEJ,
            client->player);
}

static void handle_command_enqueue(server_t *server, client_t *client,
    const char *clean, const char *cmd_name)
{
    int ticks = server->vtable->get_command_delay(server, clean);

    console_log(LOG_INFO, "handle poll: %s / current tick game %d", clean,
        server->game->tick_counter);
    maybe_emit_gui_command_event(server, client, cmd_name);
    if (!client_enqueue_command(client, clean, ticks, server->game)) {
        console_log(LOG_WARNING,
            "Client %d: command queue full, dropped \"%s\"",
            client->fd, clean);
    }
}

void process_command_line(server_t *server, client_t *client, const char *line)
{
    char clean[BUFFER_COMMAND_SIZE] = {0};
    char cmd_name[BUFFER_CMD_NAME] = {0};

    if (!server || !client || !line)
        return;
    strncpy(clean, line, BUFFER_COMMAND_SIZE - 1);
    clean[BUFFER_COMMAND_SIZE - 1] = '\0';
    strip_linefeed(clean);
    extract_command_name(clean, cmd_name, sizeof(cmd_name));
    if (client->type == CLIENT_GUI) {
        handle_gui_command(server, client, cmd_name, clean);
        return;
    }
    handle_command_enqueue(server, client, clean, cmd_name);
}

/**
 * @brief Extracts commands from the client's read buffer and processes them.
 *
 * This function searches for newline characters in the client's read buffer,
 * extracts complete command lines, and processes each command line.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client instance.
 */
static void extract_commands_from_buffer(server_t *server,
    client_t *client)
{
    char *newline = NULL;
    size_t line_len = 0;
    size_t remaining = 0;
    char line[BUFFER_COMMAND_SIZE] = {0};

    newline = memchr(client->read_buffer, '\n', client->buffer_len);
    while (newline != NULL) {
        line_len = newline - client->read_buffer + 1;
        line_len = (line_len >= BUFFER_COMMAND_SIZE)
            ? BUFFER_COMMAND_SIZE - 1 : line_len;
        memset(line, 0, sizeof(line));
        memcpy(line, client->read_buffer, line_len);
        line[line_len] = '\0';
        process_command_line(server, client, line);
        remaining = client->buffer_len - line_len;
        memmove(client->read_buffer,
            client->read_buffer + line_len, remaining);
        client->buffer_len = remaining;
        newline = memchr(client->read_buffer, '\n', client->buffer_len);
    }
}

/**
 * @brief Appends data to the client's read buffer.
 *
 * This function copies the specified number of bytes from the provided buffer
 * to the client's read buffer, updating the buffer length accordingly.
 *
 * @param client Pointer to the client instance.
 * @param buf Pointer to the data buffer to append.
 * @param bytes Number of bytes to append.
 */
static void append_to_read_buffer(client_t *client,
    const char *buf, ssize_t bytes)
{
    memcpy(client->read_buffer + client->buffer_len, buf, bytes);
    client->buffer_len += bytes;
    client->read_buffer[client->buffer_len] = '\0';
}

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
