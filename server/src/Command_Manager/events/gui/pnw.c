/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** pnw.c
*/

#include "client.h"
#include "game.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT GUI                                    */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Handles the "pnw" event for GUI clients.
 *
 * This function constructs a response payload containing the new player's
 * information and sends it to the GUI client.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the client that just joined
 */
void handle_gui_pnw(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    client_t *gui;
    response_payload_t *payload;

    if (!server || !client || !client->player)
        return;
    gui = server->vtable->get_gui(server);
    if (!gui)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    asprintf(&payload->message, "pnw #%d %d %d %d %d %s\n", client->player->id,
        client->player->x, client->player->y, client->player->orientation,
        client->player->level, client->player->team_name);
    if (!payload->message)
        return;
    payload->client = gui;
    EMIT(server->dispatcher, "send_response", payload);
}
