/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emit a "bct X Y" command for a single tile to the GUI.
 *
 * If a command is provided, it is overwritten with the "bct X Y" string.
 *
 * @param srv Pointer to the server instance.
 * @param cli Pointer to the GUI client.
 * @param cmd Pointer to the current queued command (can be NULL).
 * @param pos Position of the tile to emit (X, Y).
 */
static void emit_bct_for_tile(server_t *srv, client_t *cli,
    queued_command_t *cmd, vector2i_t pos)
{
    char bct[BUFFER_COMMAND_SIZE] = {0};

    snprintf(bct, sizeof(bct), "bct %d %d", pos.x, pos.y);
    if (cmd) {
        strncpy(cmd->content, bct, sizeof(cmd->content) - 1);
        cmd->content[sizeof(cmd->content) - 1] = '\0';
    }
    EMIT(srv->command_manager->dispatcher, CMD_GUI_BCT, cli);
}

/**
 * @brief Emit "bct" commands for every tile on the map to the GUI.
 *
 * Iterates over the full map grid and emits each tile's state.
 * Restores the original command content after emission.
 *
 * @param srv Pointer to the server instance.
 * @param cli Pointer to the GUI client.
 * @param cmd Pointer to the current queued command (can be NULL).
 * @param backup Backup string of the original command content.
 */
static void emit_bct_for_tile_range(server_t *srv, client_t *cli,
    queued_command_t *cmd, char *backup)
{
    vector2i_t pos;

    for (pos.y = 0; pos.y < srv->game->height; pos.y++) {
        for (pos.x = 0; pos.x < srv->game->width; pos.x++) {
            emit_bct_for_tile(srv, cli, cmd, pos);
        }
    }
    if (cmd) {
        strncpy(cmd->content, backup, sizeof(cmd->content) - 1);
        cmd->content[sizeof(cmd->content) - 1] = '\0';
    }
}

/**
 * @brief Handle the "mct" command from the GUI.
 *
 * Emits a "bct" response for every tile. If no command is queued,
 * a temporary one is enqueued and removed after processing.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the GUI client.
 */
void handle_command_gui_mct(void *ctx, void *data)
{
    server_t *srv = ctx;
    client_t *cli = data;
    queued_command_t *cmd = NULL;
    char backup[BUFFER_COMMAND_SIZE] = {0};
    bool temp = false;

    if (!srv || !cli)
        return;
    cmd = client_peek_command(cli);
    if (!cmd) {
        client_enqueue_command(cli, "mct", 0.0f, srv->game);
        temp = true;
        cmd = client_peek_command(cli);
    }
    if (cmd)
        strncpy(backup, cmd->content, sizeof(backup) - 1);
    emit_bct_for_tile_range(srv, cli, cmd, backup);
    if (temp)
        client_dequeue_command(cli, NULL);
}
