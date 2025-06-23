/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** pin.c
*/

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

#include "client.h"
#include "game.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

/**
* @brief Handles the error checking for the PIN command.
* @param args_line The line containing the command arguments.
* @param arg Buffer to store the extracted argument.
* @param client_num Pointer to store the player number.
* @param server Pointer to the server structure.
* @return true if no errors, false if an error occurred.
*/
static bool error_handling(char *args_line, char *arg, int *client_num,
    server_t *server)
{
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PIN: Missing parameter");
        EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
        return false;
    }
    *client_num = get_player_number(arg);
    if (*client_num < 0) {
        EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
        return false;
    }
    return true;
}

/**
 * @brief Sends the player's inventory to the GUI client.
 *
 * Formats and sends the player's inventory in the format:
 * "pin #<player_id> <x> <y> <food> <linemate> <deraumere> <sibur>
 * <mendiane> <phiras> <thystame>\n".
 *
 * @param client Pointer to the GUI client.
 * @param player Pointer to the player whose inventory is being sent.
 */
static void pin_send_inventory(client_t *client, player_t *player)
{
    dprintf(client->fd, "pin #%d %d %d %d %d %d %d %d %d %d\n",
        player->id, player->x, player->y,
        player->inventory[RESOURCE_FOOD],
        player->inventory[RESOURCE_LINEMATE],
        player->inventory[RESOURCE_DERAUMERE],
        player->inventory[RESOURCE_SIBUR],
        player->inventory[RESOURCE_MENDIANE],
        player->inventory[RESOURCE_PHIRAS],
        player->inventory[RESOURCE_THYSTAME]);
}

/**
 * @brief Handles the PIN command from a GUI client.
 *
 * Retrieves the player's inventory and sends it to the GUI client
 * in the format: "pin #<player_id> <x> <y> <food> <linemate> <deraumere>
 * <sibur> <mendiane> <phiras> <thystame>\n".
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_pin(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = NULL;
    char args_line[BUFFER_COMMAND_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    int client_num = -1;

    if (!client || !client)
        return;
    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE)
        || !error_handling(args_line, arg, &client_num, server))
        return;
    player = find_player_by_id(server->game, client_num);
    if (!player) {
        console_log(LOG_WARNING, "PIN: Player %d not found", client_num);
        EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
        return;
    }
    pin_send_inventory(client, player);
}

/**
 * @brief Handles the PIN command for a GUI client.
 *
 * Retrieves the player's inventory and sends it to the GUI client
 * in the format: "pin #<player_id> <x> <y> <food> <linemate> <deraumere>
 * <sibur> <mendiane> <phiras> <thystame>\n".
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the player whose inventory is being requested.
 */
void handle_gui_pin(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *client = NULL;

    if (!server || !player)
        return;
    client = server->gui;
    if (!client)
        return;
    pin_send_inventory(client, player);
}
