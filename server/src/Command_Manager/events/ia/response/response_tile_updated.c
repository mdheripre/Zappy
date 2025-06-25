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
 * @brief Backup and replace the content of a queued command.
 *
 * Used to temporarily override a command during GUI emission.
 *
 * @param cmd Pointer to the command to modify.
 * @param new_content New content to set.
 * @param backup Buffer to store the original content.
 * @param backup_size Size of the backup buffer.
 */
static void backup_and_replace_command_content(queued_command_t *cmd,
    const char *new_content, char *backup, size_t backup_size)
{
    if (!cmd || !new_content || !backup)
        return;
    strncpy(backup, cmd->content, backup_size - 1);
    backup[backup_size - 1] = '\0';
    strncpy(cmd->content, new_content, sizeof(cmd->content) - 1);
    cmd->content[sizeof(cmd->content) - 1] = '\0';
}

/**
 * @brief Build a "bct X Y" command string from a tile update event.
 *
 * @param buffer Output buffer to write the command string.
 * @param buffer_size Size of the output buffer.
 * @param event Pointer to the tile update event.
 */
static void build_bct_command(char *buffer, size_t buffer_size,
    const game_event_t *event)
{
    if (!buffer || !event)
        return;
    snprintf(buffer, buffer_size, "bct %d %d", event->data.tile.x,
        event->data.tile.y);
}

/**
 * @brief Prepare and emit a "bct" command for a tile update to the GUI.
 *
 * Temporarily overrides the command if needed and restores it after sending.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the GUI client.
 * @param event Pointer to the tile update event.
 */
static void prepare_and_emit_bct(server_t *server,
    client_t *client, game_event_t *event)
{
    queued_command_t *cmd = client_peek_command(client);
    char backup[BUFFER_COMMAND_SIZE] = {0};
    char tmp[BUFFER_COMMAND_SIZE] = {0};
    bool created_temp = false;

    if (!server || !client || !event)
        return;
    build_bct_command(tmp, sizeof(tmp), event);
    if (!cmd) {
        client_enqueue_command(client, tmp, 0, server->game);
        created_temp = true;
    } else
        backup_and_replace_command_content(cmd, tmp, backup, sizeof(backup));
    EMIT(server->command_manager->dispatcher, CMD_GUI_BCT, client);
    if (created_temp)
        client_dequeue_command(client, NULL);
    else if (cmd) {
        strncpy(cmd->content, backup, sizeof(cmd->content) - 1);
        cmd->content[sizeof(cmd->content) - 1] = '\0';
    }
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
    client_t *client = server->gui;

    if (!server || !event || !client)
        return;
    prepare_and_emit_bct(server, client, event);
}
