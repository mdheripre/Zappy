/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** inventory
*/

#include "server.h"
#include "player.h"
#include "game.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Format a player's inventory into a readable string.
 *
 * @param player Pointer to the player.
 * @return Newly allocated string containing the inventory.
 */
static char *format_inventory(player_t *player)
{
    char *buffer = calloc(BUFFER_COMMAND_SIZE, sizeof(char));

    if (!buffer)
        return NULL;
    snprintf(buffer, BUFFER_COMMAND_SIZE,
        "[ food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
        player->inventory[RESOURCE_FOOD],
        player->inventory[RESOURCE_LINEMATE],
        player->inventory[RESOURCE_DERAUMERE],
        player->inventory[RESOURCE_SIBUR],
        player->inventory[RESOURCE_MENDIANE],
        player->inventory[RESOURCE_PHIRAS],
        player->inventory[RESOURCE_THYSTAME]
    );
    return buffer;
}

/**
 * @brief Send a response containing the player's inventory.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player.
 * @param event Original inventory request event.
 */
static void send_inventory_response(game_t *game, player_t *player,
    game_event_t *event)
{
    char *inventory_str = format_inventory(player);
    game_event_t *response = NULL;

    if (!inventory_str)
        return;
    response = malloc(sizeof(game_event_t));
    if (!response) {
        free(inventory_str);
        return;
    }
    response->type = GAME_EVENT_RESPONSE_INVENTORY;
    response->data.generic_response.client_fd =
        event->data.generic_response.client_fd;
    response->data.generic_response.response = inventory_str;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}

/**
 * @brief Handle an inventory request from a player.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the inventory event.
 */
void on_inventory(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *player = NULL;

    if (!game || !event)
        return;
    player = find_player_by_id(game, event->data.generic_response.player_id);
    if (!player)
        return;
    send_inventory_response(game, player, event);
}
