/*
** EPITECH PROJECT, 2025
** server
** File description:
** number_player
*/

#include "game.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Prepares the response event for connect_nbr.
 *
 * @param player The player requesting the number of available slots.
 * @param event The original event triggering the response.
 * @param available The number of available slots.
 * @return game_event_t* The prepared response event, or NULL on failure.
 */
static game_event_t *prepare_connect_nbr_response(player_t *player,
    game_event_t *event, int available)
{
    char buffer[BUFFER_SIZE];
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return NULL;
    snprintf(buffer, sizeof(buffer), "%d\n", available);
    response->type = GAME_EVENT_RESPONSE_CONNECT_NBR;
    response->data.generic_response.client_fd = event->
    data.generic_response.client_fd;
    response->data.generic_response.player_id = player->id;
    response->data.generic_response.response = strdup(buffer);
    if (!response->data.generic_response.response) {
        free(response);
        return NULL;
    }
    return response;
}

/**
 * @brief Count the number of unassigned eggs available for a player's team.
 *
 * Only eggs with a matching team name and no assigned player are counted.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player whose team is checked.
 * @return Number of available slots (eggs), or -1 on error.
 */
static int get_team_available_slots(game_t *game, player_t *player)
{
    egg_t *egg = NULL;
    int count = 0;

    if (!game || !player || !player->team_name || !game->eggs)
        return -1;
    for (list_node_t *node = game->eggs->head; node; node = node->next) {
        egg = node->data;
        if (egg && strcmp(egg->team_name, player->team_name) == 0
            && egg->player_id == -1)
            count++;
    }
    return count;
}

/**
 * @brief Handles the connect_nbr event, sending the number of available slots
 *        to the player.
 *
 * @param ctx The game context.
 * @param data The event data.
 */
void on_connect_nbr(void *ctx, void *data)
{
    game_t *game = (game_t *)ctx;
    game_event_t *event = (game_event_t *)data;
    player_t *player = NULL;
    int available = 0;
    game_event_t *response = NULL;

    if (!game || !event)
        return;
    player = find_player_by_id(game, event->data.generic_response.player_id);
    available = get_team_available_slots(game, player);
    if (available < 0)
        return;
    response = prepare_connect_nbr_response(player, event, available);
    if (!response)
        return;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}
