/*
** EPITECH PROJECT, 2025
** server
** File description:
** init_server
*/


#include "utils.h"
#include "server.h"
#include "shared.h"

/****************************************************************************/
/*                                                                          */
/*                        METHODS DECLARATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Default method table for the server object.
 *
 * Contains function pointers for server operations such as construction,
 * running, destruction, polling, client management, and command delay
 * retrieval.
 */
static const server_methods_t DEFAULT_SERVER_METHODS = {
    .constructor = init_socket,
    .run = run_server,
    .destroy = server_destroy,
    .setup_poll = setup_server_poll,
    .handle_poll = handle_server_poll,
    .accept_client = accept_client,
    .remove_client = remove_client,
    .get_command_delay = get_command_delay
};

/****************************************************************************/
/*                                                                          */
/*                      EVENT GLOBAL DECLARATION                            */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Registers core event handlers to the server's dispatcher.
 *
 * @param server Pointer to the server instance.
 */
static void register_core_events(server_t *server)
{
    REGISTER(server->dispatcher, "client_connected",
        on_client_connected, NULL);
    REGISTER(server->dispatcher, "client_identify",
        on_client_identify, server);
    REGISTER(server->dispatcher, "send_response", on_send_response, NULL);
}

/****************************************************************************/
/*                                                                          */
/*                            CONSTRUCTOR                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Creates a TCP socket for the server.
 *
 * @param self Pointer to the server structure.
 * @return true if the socket was created successfully, false otherwise.
 */
static bool create_socket(server_t *self)
{
    self->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (self->socket_fd == -1) {
        console_log(LOG_ERROR, "Failed to create socket");
        return false;
    }
    return true;
}

/**
 * @brief Sets socket options for the server socket.
 *
 * Enables the SO_REUSEADDR option on the server's socket file descriptor.
 *
 * @param self Pointer to the server structure.
 * @return true on success, false on failure.
 */
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

/**
 * @brief Initializes the server address structure with family, IP, and port.
 *
 * @param self Pointer to the server structure to configure.
*/
static void setup_address(server_t *self)
{
    self->address.sin_family = AF_INET;
    self->address.sin_addr.s_addr = INADDR_ANY;
    self->address.sin_port = htons(self->port);
}

/**
 * @brief Binds the server socket to the specified address and port.
 *
 * @param self Pointer to the server structure.
 * @return true if binding was successful, false otherwise.
 */
static bool bind_socket(server_t *self)
{
    if (bind(self->socket_fd, (struct sockaddr *)&self->address,
        sizeof(self->address)) == -1) {
        console_log(LOG_ERROR, "Bind failed on port %d", self->port);
        return false;
    }
    return true;
}

/**
 * @brief Listens for incoming connections on the server socket.
 *
 * Configures the server socket to listen for incoming client connections.
 *
 * @param self Pointer to the server structure.
 * @return true if listening was successful, false otherwise.
 */
static bool listen_socket(server_t *self)
{
    if (listen(self->socket_fd, MAX_CLIENTS) == -1) {
        console_log(LOG_ERROR, "Listen failed");
        return false;
    }
    console_log(LOG_SUCCESS, "Server listening on port %d", self->port);
    return true;
}

/**
 * @brief Initializes the server socket and prepares it for accepting
 * connections.
 *
 * This function creates a socket, sets options, binds it to an address,
 * and starts listening for incoming connections.
 *
 * @param self Pointer to the server structure.
 * @return true if all operations were successful, false otherwise.
 */
bool init_socket(server_t *self)
{
    return create_socket(self) && set_socket_options(self) &&
    (setup_address(self), true) && bind_socket(self) && listen_socket(self);
}

/**
 * @brief Initializes the server structure with default values and methods.
 *
 * This function sets up the server's port, frequency, and dispatcher,
 * and registers core events and commands.
 *
 * @param server Pointer to the server structure to initialize.
 * @param port The port number for the server to listen on.
 * @return true if initialization was successful, false otherwise.
 */
bool server_init(server_t *server, int port)
{
    if (!server)
        return false;
    memset(server, 0, sizeof(server_t));
    server->port = port;
    server->vtable = &DEFAULT_SERVER_METHODS;
    server->frequency = 1.0f;
    if (!server->vtable->constructor(server)) {
        console_log(LOG_ERROR, "Failed to initialize server");
        return false;
    }
    server->dispatcher = NEW(dispatcher, on_event_not_found);
    if (!server->dispatcher) {
        console_log(LOG_ERROR, "Failed to create dispatcher");
        return false;
    }
    register_core_events(server);
    return true;
}

/****************************************************************************/
/*                                                                          */
/*                        PUBLIC CONSTRUCTOR                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Creates and initializes a new server instance.
 *
 * Allocates memory for a server, initializes it with the given port,
 * creates the game and command manager, and registers all commands.
 *
 * @param port The port number for the server to listen on.
 * @param width The width of the game map.
 * @param height The height of the game map.
 * @param frequency The frequency for the game loop.
 * @return Pointer to the created server_t, or NULL on failure.
 */
server_t *server_create(int port, int width, int height, float frequency)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server)
        return NULL;
    if (!server_init(server, port)) {
        free(server);
        return NULL;
    }
    server->game = NEW(game, width, height, frequency);
    if (!server->game) {
        return NULL;
    }
    server->command_manager = NEW(command_manager);
    if (!server->command_manager) {
        console_log(LOG_ERROR, "Failed to create command manager");
        return NULL;
    }
    server->command_manager->methods->register_all(server->command_manager);
    return server;
}
