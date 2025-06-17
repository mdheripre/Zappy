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
 * @brief Process a raw command line from a client.
 *
 * Cleans the line, determines its delay, and enqueues it if possible.
 * Logs a warning if the client's command queue is full.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client sending the command.
 * @param line Raw command line string.
 */
void process_command_line(server_t *server, client_t *client,
    const char *line)
{
    char clean[BUFFER_COMMAND_SIZE] = {0};
    int ticks = 0;

    if (!server || !client || !line)
        return;
    strncpy(clean, line, BUFFER_COMMAND_SIZE - 1);
    clean[BUFFER_COMMAND_SIZE - 1] = '\0';
    strip_linefeed(clean);
    ticks = server->vtable->get_command_delay(server, clean);
    console_log(LOG_INFO, "handle poll: %s / current tick game %d", clean,
        server->game->tick_counter);
    if (!client_enqueue_command(client, clean, ticks, server->game)) {
        console_log(LOG_WARNING,
            "Client %d: command queue full, dropped \"%s\"",
            client->fd, clean);
    }
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

/**
 * @brief Reads data from a client socket and processes it.
 *
 * This function reads data from the specified client socket, appends it to
 * the client's read buffer, and extracts commands from the buffer.
 * If the read operation fails or the buffer overflows, it removes the client.
 *
 * @param server Pointer to the server instance.
 * @param index Index of the client in the server's client array.
 */
void read_from_client(server_t *server, int index)
{
    client_t *client = &server->clients[index];
    char buf[BUFFER_COMMAND_SIZE] = {0};
    ssize_t bytes = 0;

    bytes = read(client->fd, buf, sizeof(buf));
    if (bytes <= 0) {
        console_log(LOG_INFO,
            "Client (fd=%d) disconnected", client->fd);
        server->vtable->remove_client(server, index);
        return;
    }
    if (client->buffer_len + bytes >= CLIENT_BUFFER_SIZE) {
        console_log(LOG_WARNING,
            "Buffer overflow for client %d", client->fd);
        dprintf(client->fd, "ko\n");
        server->vtable->remove_client(server, index);
        return;
    }
    append_to_read_buffer(client, buf, bytes);
    extract_commands_from_buffer(server, client);
}

/**
 * @brief Sets up the poll file descriptors for the server and its clients.
 *
 * This function initializes the poll file descriptors for the server socket
 * and all connected clients, preparing them for polling events.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of poll file descriptors to populate.
 * @param nfds Pointer to the number of file descriptors in the array.
 */
void handle_server_poll(server_t *self, struct pollfd *fds)
{
    int client_index = 0;
    int i = 0;

    if (fds[0].revents & POLLIN)
        self->vtable->accept_client(self);
    for (i = 1; i <= self->client_count; i++) {
        if (fds[i].revents & (POLLIN | POLLHUP)) {
            read_from_client(self, client_index);
            continue;
        }
        client_index++;
    }
}
