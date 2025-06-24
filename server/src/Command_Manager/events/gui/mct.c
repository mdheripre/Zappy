/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emit a "bct" command for each tile on the map.
 *
 * Used to simulate multiple GUI requests from a single "mct" command.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client issuing the command.
 * @param cmd Pointer to the queued command being processed.
 */
static void emit_bct_for_all_tiles(server_t *server, client_t *client,
    queued_command_t *cmd)
{
    char bct_cmd[BUFFER_COMMAND_SIZE] = {0};

    for (int y = 0; y < server->game->height; y++) {
        for (int x = 0; x < server->game->width; x++) {
            snprintf(bct_cmd, sizeof(bct_cmd), "bct %d %d", x, y);
            strncpy(cmd->content, bct_cmd, sizeof(cmd->content) - 1);
            cmd->content[sizeof(cmd->content) - 1] = '\0';
            EMIT(server->command_manager->dispatcher, CMD_GUI_BCT, client);
        }
    }
}

/**
 * @brief Handle the GUI "mct" command (map content).
 *
 * Emits a "bct" command for each tile on the map to provide full map data.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the client issuing the command.
 */
void handle_command_gui_mct(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    queued_command_t *cmd = NULL;
    char backup[BUFFER_COMMAND_SIZE] = {0};

    if (!server || !client)
        return;
    cmd = client_peek_command(client);
    if (!cmd)
        return;
    strncpy(backup, cmd->content, sizeof(backup) - 1);
    backup[sizeof(backup) - 1] = '\0';
    emit_bct_for_all_tiles(server, client, cmd);
    strncpy(cmd->content, backup, sizeof(cmd->content) - 1);
    cmd->content[sizeof(cmd->content) - 1] = '\0';
}
