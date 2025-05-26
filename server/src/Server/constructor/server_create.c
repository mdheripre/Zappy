/*
** EPITECH PROJECT, 2025
** server
** File description:
** init_server
*/


#include "utils.h"
#include "server.h"
#include "shared.h"

static const server_methods_t DEFAULT_SERVER_METHODS = {
    .constructor = init_socket,
    .run = run_server,
    .destroy = server_destroy,
    .setup_poll = setup_server_poll,
    .handle_poll = handle_server_poll,
    .accept_client = accept_client,
    .remove_client = remove_client
};

static bool create_socket(server_t *self)
{
    self->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (self->socket_fd == -1) {
        console_log(LOG_ERROR, "Failed to create socket");
        return false;
    }
    return true;
}

static bool set_socket_options(server_t *self)
{
    int opt = 1;

    if (setsockopt(self->socket_fd, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt)) == -1) {
        console_log(LOG_ERROR, "setsockopt failed");
        return false;
    }
    return true;
}

static void setup_address(server_t *self)
{
    self->address.sin_family = AF_INET;
    self->address.sin_addr.s_addr = INADDR_ANY;
    self->address.sin_port = htons(self->port);
}

static bool bind_socket(server_t *self)
{
    if (bind(self->socket_fd, (struct sockaddr *)&self->address,
        sizeof(self->address)) == -1) {
        console_log(LOG_ERROR, "Bind failed on port %d", self->port);
        return false;
    }
    return true;
}

static bool listen_socket(server_t *self)
{
    if (listen(self->socket_fd, MAX_CLIENTS) == -1) {
        console_log(LOG_ERROR, "Listen failed");
        return false;
    }
    console_log(LOG_SUCCESS, "Server listening on port %d", self->port);
    return true;
}

bool init_socket(server_t *self)
{
    return create_socket(self)
        && set_socket_options(self)
        && (setup_address(self), true)
        && bind_socket(self)
        && listen_socket(self);
}

static void register_core_events(server_t *server)
{
    REGISTER(server->dispatcher, "client_connected",
        on_client_connected, NULL);
}

bool server_init(server_t *server, int port)
{
    if (!server)
        return false;
    memset(server, 0, sizeof(server_t));
    server->port = port;
    server->vtable = &DEFAULT_SERVER_METHODS;
    if (!server->vtable->constructor(server)) {
        console_log(LOG_ERROR, "Failed to initialize server");
        return false;
    }
    server->dispatcher = NEW(dispatcher);
    if (!server->dispatcher) {
        console_log(LOG_ERROR, "Failed to create dispatcher");
        return false;
    }
    register_core_events(server);
    command_manager_register_all(server);
    return true;
}

server_t *server_create(int port)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server)
        return NULL;
    if (!server_init(server, port)) {
        free(server);
        return NULL;
    }
    return server;
}
