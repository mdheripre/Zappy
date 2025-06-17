/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_tile_updated
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Prepare and emit a "bct" command for a specific tile.
 *
 * Temporarily overwrites the current command to trigger a tile update.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the GUI client.
 * @param event Pointer to the tile update event.
 */
static void prepare_and_emit_bct(server_t *server, client_t *client,
    game_event_t *event)
{
    queued_command_t *cmd = NULL;
    char backup[BUFFER_COMMAND_SIZE] = {0};
    char temp_cmd[BUFFER_COMMAND_SIZE] = {0};

    cmd = client_peek_command(client);
    if (!cmd)
        return;
    strncpy(backup, cmd->content, sizeof(backup) - 1);
    backup[sizeof(backup) - 1] = '\0';
    snprintf(temp_cmd, sizeof(temp_cmd), "bct %d %d",
        event->data.tile.x, event->data.tile.y);
    strncpy(cmd->content, temp_cmd, sizeof(cmd->content) - 1);
    cmd->content[sizeof(cmd->content) - 1] = '\0';
    EMIT(server->command_manager->dispatcher, "command_gui_bct", client);
    strncpy(cmd->content, backup, sizeof(backup) - 1);
    cmd->content[sizeof(backup) - 1] = '\0';
}

/**
 * @brief Handle a tile update event by emitting a "bct" for the GUI.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the tile update event.
 */
void on_response_tile_updated(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = get_gui_client(server);

    if (!server || !event || !client)
        return;
    prepare_and_emit_bct(server, client, event);
}
