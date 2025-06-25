/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** sst.c
*/

#include "client.h"
#include "command_manager.h"
#include "game.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

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
* @param num int pointer where too store the wanted frequency after extraction.
* @return bool true if no error false otherwise
*/
static bool sst_error_handling(const char *args_line, char *arg, int *freq)
{
    if (!get_next_arg((char *)args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "SST: Missing parameter");
        return false;
    }
    *freq = get_frequency_from_str(arg);
    if (*freq <= 0) {
        console_log(LOG_WARNING, "SST: Invalid frequency value");
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
    char args_line[CLIENT_BUFFER_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    int freq = 0;

    if (!server || !client)
        return;
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, CLIENT_BUFFER_SIZE)
        || !sst_error_handling(args_line, arg, &freq)) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return;
    }
    server->game->frequency = freq;
    dprintf(client->fd, "sst %d\n", freq);
}
