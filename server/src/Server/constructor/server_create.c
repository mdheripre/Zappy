/*
** EPITECH PROJECT, 2025
** server
** File description:
** init_server
*/


#include "config.h"
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
    .get_command_delay = get_command_delay,
    .reject_client = reject_client,
    .get_gui = server_get_gui,
    .get_next_tick_info = get_next_tick_info,
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
        on_client_connected, server);
    REGISTER(server->dispatcher, "client_identify",
        on_client_identify, server);
    REGISTER(server->dispatcher, "send_response", on_send_response, server);
    REGISTER(server->dispatcher, "gui_init", on_gui_init, server);
    REGISTER(server->dispatcher, "ia_init", on_ia_init, server);
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
 * @brief Initializes the core state of a server instance.
 *
 * Sets default values, assigns the method table, constructs the internal
 * dispatcher, and registers core events. Does not allocate memory for
 * the server itself.
 *
 * @param server Pointer to the server structure to initialize.
 * @param config Pointer to the configuration used for setup.
 * @return true if initialization succeeded, false otherwise.
 */
bool server_init(server_t *server, config_t *config)
{
    if (!server || !config)
        return false;
    memset(server, 0, sizeof(server_t));
    server->port = config->port;
    server->vtable = &DEFAULT_SERVER_METHODS;
    if (!server->vtable->constructor(server))
        return false;
    server->dispatcher = NEW(dispatcher, on_event_not_found);
    if (!server->dispatcher)
        return false;
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
 * Allocates the server structure and initializes its core components,
 * including the game instance and command manager. Fails gracefully on
 * any allocation or initialization error.
 *
 * @param config Pointer to the server configuration structure.
 * @return Pointer to the newly created server, or NULL on failure.
 */
server_t *server_create(config_t *config)
{
    server_t *server = malloc(sizeof(server_t));
    config_game_t game_cfg = { .width = config->width,
        .height = config->height, .frequency = config->frequency,
        .team_size = config->team_size, .team_name = config->team_name
    };

    if (!server_init(server, config)) {
        free(server);
        return NULL;
    }
    server->game = NEW(game, &game_cfg);
    server->clients = NEW(list, free);
    server->command_manager = NEW(command_manager);
    if (!server->command_manager || !server->game) {
        free(server);
        return NULL;
    }
    server->command_manager->methods->register_all(server->command_manager,
        server);
    return server;
}
