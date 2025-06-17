/*
** EPITECH PROJECT, 2025
** server
** File description:
** sbp
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the "suc" command for the GUI client.
 *
 * Allocates and sends a "suc\n" response to the GUI client if connected.
 *
 * @param ctx Pointer to the server context.
 * @param data Unused parameter.
 */
void handle_gui_suc(void *ctx, void *)
{
    server_t *server = ctx;
    client_t *client = server->vtable->get_gui(server);
    response_payload_t *payload = NULL;

    if (!client)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup("suc\n");
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
