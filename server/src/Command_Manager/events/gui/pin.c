/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** pin.c
*/

#include "client.h"
#include "game.h"
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
* @brief Handles the error checking for the PIN command.
* @param args_line The line containing the command arguments.
* @param arg Buffer to store the extracted argument.
* @param client_num Pointer to store the player number.
* @return true if no errors, false if an error occurred.
*/
static bool error_handling_pin(char *args_line, char *arg,
    int *client_num)
{
    if (!get_next_arg(args_line, arg, BUFFER_SIZE)) {
        console_log(LOG_WARNING, "PIN: Missing parameter");
        return false;
    }
    *client_num = get_player_number(arg);
    return *client_num >= 0;
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

static player_t *get_player_from_pin_command(server_t *server,
    client_t *client, int *client_num)
{
    char args_line[BUFFER_COMMAND_SIZE] = {0};
    char arg[BUFFER_SIZE] = {0};
    player_t *player = NULL;

    if (!extract_command_arguments(client_peek_command(client)->content,
        args_line, BUFFER_COMMAND_SIZE) ||
        !error_handling_pin(args_line, arg, client_num)) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
        return NULL;
    }
    player = find_player_by_id(server->game, *client_num);
    if (!player) {
        console_log(LOG_WARNING, "PIN: Player %d not found", *client_num);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_SBP, NULL);
    }
    return player;
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
    int client_num = -1;
    player_t *player = NULL;

    if (!server || !client)
        return;
    player = get_player_from_pin_command(server, client, &client_num);
    if (!player)
        return;
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
