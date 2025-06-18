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
 * @param client Pointer to the client issuing the command.
 * @return true if no errors, false if an error occurred.
 */
static bool error_handling(char *args_line, char *arg, int *client_num,
    client_t *client)
{
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE))
        return false;
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PPO: Missing parameter");
        // emit error arg
        return false;
    }
    *client_num = get_player_number(arg);
    if (*client_num < 0) {
        // emit error arg
        return false;
    }
    return true;
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
    if (!error_handling(args_line, arg, &client_num, client))
        return;
    player = find_player_by_id(server->game, client_num);
    if (!player) {
        console_log(LOG_WARNING, "PPO: Player %d not found", client_num);
        // emit error player not found
        return;
    }
    dprintf(client->fd, "ppo #%d %d %d %d\n",
        player->id, player->x, player->y, player->orientation);
}

/**
 * @brief Handles the PPO command for a GUI client.
 *
 * This function constructs the command string for the PPO command
 * and enqueues it to be processed by the GUI client.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the an int of client' id
 */
void handle_gui_ppo(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *gui_client = NULL;
    char command[BUFFER_COMMAND_SIZE] = {0};

    if (!server || !data)
        return;
    gui_client = server->vtable->get_gui(server);
    if (!gui_client)
        return;
    snprintf(command, BUFFER_COMMAND_SIZE, "ppo #%d", *(int *)data);
    command[BUFFER_COMMAND_SIZE - 1] = '\0';
    if (!client_enqueue_front_command(gui_client, command, 0.f))
        return;
    handle_command_gui_ppo(server, gui_client);
    client_dequeue_command(gui_client, NULL);
}
