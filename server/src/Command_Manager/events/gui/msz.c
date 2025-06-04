/*
** EPITECH PROJECT, 2025
** server
** File description:
** msz
*/

#include "command_manager.h"
#include "shared.h"
#include "server.h"
#include "client.h"
/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the MSZ command from a GUI client.
 *
 * Constructs and sends the map size information to the GUI client.
 * The response follows the GUI protocol format: "msz X Y\n", where
 * X and Y are the width and height of the game map.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_msz(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    char buffer[BUFFER_SIZE];
    response_payload_t *payload = NULL;

    if (!server || !client)
        return;
    snprintf(buffer, sizeof(buffer), "msz %d %d\n",
        server->game->width, server->game->height);
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(buffer);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
