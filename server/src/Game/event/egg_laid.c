/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** egg_laid
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Create a new egg based on a player's position and team.
 *
 * @param player Pointer to the player.
 * @return Pointer to the newly created egg, or NULL on failure.
 */
static egg_t *create_egg_from_player(player_t *player)
{
    static int egg_id = 1;
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->id = egg_id;
    egg_id++;
    egg->player_id = player->id;
    egg->team_name = player->team_name;
    egg->x = player->x;
    egg->y = player->y;
    return egg;
}

/**
 * @brief Create and add a new egg to the game.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player laying the egg.
 * @return Pointer to the egg, or NULL on failure.
 */
static egg_t *add_egg_to_game(game_t *game, player_t *player)
{
    egg_t *egg = create_egg_from_player(player);

    if (!egg)
        return NULL;
    game->eggs->methods->push_back(game->eggs, egg);
    return egg;
}

/**
 * @brief Send a response event indicating a new egg was laid.
 *
 * @param game Pointer to the game instance.
 * @param egg Pointer to the egg that was laid.
 */
static void send_egg_laid_event(game_t *game, egg_t *egg)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return;
    response->type = GAME_EVENT_RESPONSE_EGG_LAID;
    response->data.egg.player_id = egg->player_id;
    response->data.egg.team_name = egg->team_name;
    response->data.egg.x = egg->x;
    response->data.egg.y = egg->y;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}

/**
 * @brief Handle the egg laying game event.
 *
 * Creates and registers a new egg based on the player's state.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the egg laying event.
 */
void on_egg_laid(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *player = find_player_by_id(game,
        event->data.generic_response.player_id);
    egg_t *egg = NULL;

    if (!game || !event || !player)
        return;
    egg = add_egg_to_game(game, player);
    if (!egg)
        return;
    send_egg_laid_event(game, egg);
    printf("fin\n");
}
