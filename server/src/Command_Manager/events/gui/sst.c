/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** sst.c
*/

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

#include "client.h"
#include "command_manager.h"
#include "game.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return The number in arg string
 *
 * @param arg Pointer to the string where extract num
 * @return the int extracted
 */
static int get_frequency_from_str(char *arg)
{
    if (!is_num(arg))
        return 0;
    return atoi(arg);
}

/**
* @brief Handles errors checkk for sst command
* @param args_line The line containing the remaining arguments.
* @param arg Buffer to store extracted argument.
* @param server Pointer to the Server' structure
* @param num int pointer where too store the wanted frequency after extraction.
* @return bool true if no error false otherwise
*/
static bool error_handling(char *args_line, char *arg, server_t *server,
    int *num)
{
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PPO: Missing parameter");
        EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
        return false;
    }
    *num = get_frequency_from_str(arg);
    if (*num <= 0) {
        console_log(LOG_WARNING, "PPO: Wrong parameter format");
        EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
        return false;
    }
    return true;
}

/**
* @brief Handle Gui sst command
*
* Set the new server's game frequency and send it back to the GUI
*
* @param ctx Pointer to server' structure
* @param data Pointer to The GUI client
*/
void handle_command_gui_sst(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    char args_line[BUFFER_COMMAND_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    int num = 0;

    if (!server || !client)
        return;
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE)
        || error_handling(args_line, arg, server, &num))
        return;
    server->game->frequency = num;
    dprintf(client->fd, "sst %d\n", num);
}
