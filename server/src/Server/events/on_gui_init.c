/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_gui_init
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                         GUI INITIALISATION                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Initializes a GUI client after connection.
 *
 * Sets the client type to GUI, clears its player pointer, and emits
 * the MSZ, SGT, and MCT commands to initialize the GUI with map size,
 * time unit, and full map content.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the response payload containing the client.
 */
void on_gui_init(void *ctx, void *data)
{
    server_t *server = ctx;
    response_payload_t *payload = data;
    client_t *client = payload->client;

    if (!server || !client)
        return;
    client->type = CLIENT_GUI;
    client->player = NULL;
    console_log(LOG_SUCCESS, "Client %d is GUI", client->fd);
    EMIT(server->command_manager->dispatcher, "command_gui_msz", client);
    EMIT(server->command_manager->dispatcher, "command_gui_sgt", client);
    EMIT(server->command_manager->dispatcher, "command_gui_mct", client);
    EMIT(server->command_manager->dispatcher, "command_gui_tna", client);
}
