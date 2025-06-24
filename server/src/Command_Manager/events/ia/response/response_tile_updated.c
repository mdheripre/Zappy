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

static void build_bct_command(char *buffer, size_t buffer_size,
    const game_event_t *event)
{
    if (!buffer || !event)
        return;
    snprintf(buffer, buffer_size, "bct %d %d", event->data.tile.x,
        event->data.tile.y);
}

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
