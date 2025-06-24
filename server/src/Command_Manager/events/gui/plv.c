/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** plv.c
*/

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

#include "client.h"
#include "command_manager.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>

/**
* @brief Handles the error checking for the PLV command.
* @param args_line The line containing the command arguments.
* @param arg Buffer to store the extracted argument.
* @param client_num Pointer to store the player number.
* @return true if no errors, false if an error occurred.
*/
static bool error_handling(char *args_line, char *arg, int *client_num)
{
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PLV: Missing parameter");
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return false;
    }
    *client_num = get_player_number(arg);
    if (*client_num < 0) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return false;
    }
    return true;
}

/**
 * @brief Handles the PLV command from a GUI client.
 *
 * Retrieves the player's level and sends it to the GUI client
 * in the format: "plv #<player_id> <level>\n".
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_plv(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = NULL;
    char args_line[BUFFER_COMMAND_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    int client_num = -1;

    if (!server || !client)
        return;
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE)
        || !error_handling(args_line, arg, &client_num))
        return EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
    player = find_player_by_id(server->game, client_num);
    if (!player) {
        console_log(LOG_WARNING, "PLV: Player %d not found", client_num);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return;
    }
    dprintf(client->fd, "plv #%d %d\n", player->id, player->level);
}

/**
 * @brief Handles the PLV command from a GUI client.
 *
 * Retrieves the player's level and sends it to the GUI client
 * in the format: "plv #<player_id> <level>\n".
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the player ID (cast from void).
 */
void handle_gui_plv(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *gui_client = NULL;
    char command[BUFFER_COMMAND_SIZE] = {0};

    if (!server || !data)
        return;
    gui_client = server->gui;
    if (!gui_client)
        return;
    snprintf(command, BUFFER_COMMAND_SIZE, "plv #%d", *(int *)data);
    command[BUFFER_COMMAND_SIZE - 1] = '\0';
    if (!client_enqueue_front_command(gui_client, command, 0.f))
        return;
    handle_command_gui_plv(server, gui_client);
    client_dequeue_command(gui_client, NULL);
}
