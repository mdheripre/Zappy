/*
** EPITECH PROJECT, 2025
** server
** File description:
** handle_poll
*/


#include "server.h"
#include "utils.h"


static void process_command_line(client_t *client, const char *line)
{
    char clean_line[BUFFER_COMMAND_SIZE] = {0};

    strncpy(clean_line, line, BUFFER_COMMAND_SIZE - 1);
    clean_line[BUFFER_COMMAND_SIZE - 1] = '\0';
    strip_linefeed(clean_line);
    if (!client_enqueue_command(client, clean_line, 0.0f)) {
        console_log(LOG_WARNING,
            "Client %d: command queue full, dropped \"%s\"",
            client->fd, clean_line);
    }
}

static void extract_commands_from_buffer(client_t *client)
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
        process_command_line(client, line);
        remaining = client->buffer_len - line_len;
        memmove(client->read_buffer,
            client->read_buffer + line_len, remaining);
        client->buffer_len = remaining;
        newline = memchr(client->read_buffer, '\n', client->buffer_len);
    }
}

static void append_to_read_buffer(client_t *client,
    const char *buf, ssize_t bytes)
{
    memcpy(client->read_buffer + client->buffer_len, buf, bytes);
    client->buffer_len += bytes;
    client->read_buffer[client->buffer_len] = '\0';
}

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
        server->vtable->remove_client(server, index);
        return;
    }
    append_to_read_buffer(client, buf, bytes);
    extract_commands_from_buffer(client);
}

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
