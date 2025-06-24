/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** ppo.c
*/

#include "client.h"
#include "command_manager.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the error checking for the PPO command.
 * @param args_line The line containing the command arguments.
 * @param arg Buffer to store the extracted argument.
 * @param client_num Pointer to store the player number.
 * @return true if no errors, false if an error occurred.
 */
static bool error_handling(char *args_line, char *arg, int *client_num)
{
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PPO: Missing parameter");
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
 * @brief Sends the player's position to the GUI client.
 *
 * Formats and sends the player's position in the format:
 * "ppo #<player_id> <x> <y> <orientation>\n".
 *
 * @param client Pointer to the GUI client.
 * @param player Pointer to the player whose position is being sent.
 */
static void ppo_send_position(client_t *client, player_t *player)
{
    dprintf(client->fd, "ppo #%d %d %d %d\n",
        player->id, player->x, player->y, player->orientation);
}

/**
 * @brief Handles the PPO command from a GUI client.
 *
 * get player position and sends it to GUI
 * in the format: "ppo #<player_id> <x> <y> <orientation>\n".
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_ppo(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    char args_line[BUFFER_COMMAND_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    int client_num = -1;
    player_t *player = NULL;

    if (!server || !client)
        return;
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE)
        || !error_handling(args_line, arg, &client_num))
        return EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
    player = find_player_by_id(server->game, client_num);
    if (!player) {
        console_log(LOG_WARNING, "PPO: Player %d not found", client_num);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return;
    }
    ppo_send_position(client, player);
}

/**
 * @brief Handles the PPO command for a GUI client.
 *
 * This function constructs the command string for the PPO command
 * and enqueues it to be processed by the GUI client.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the player whose position is being sent.
 */
void handle_gui_ppo(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui_client = NULL;

    if (!server || !player)
        return;
    gui_client = server->gui;
    if (!gui_client)
        return;
    ppo_send_position(gui_client, player);
}
