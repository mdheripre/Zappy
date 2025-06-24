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

static egg_t *create_egg_from_player(player_t *player, game_t *game)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->id = game->egg_id_current;
    game->egg_id_current++;
    egg->player = player;
    egg->team_name = player->team_name;
    egg->x = player->x;
    egg->y = player->y;
    return egg;
}

/**
 * @brief Create and add a new egg to the game.
 *
 * Also increments the team's available slots if the team is found.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player laying the egg.
 * @return Pointer to the added egg, or NULL on failure.
 */
static egg_t *add_egg_to_game(game_t *game, player_t *player)
{
    egg_t *egg = create_egg_from_player(player, game);
    team_info_t *team = find_team(game, player->team_name);

    if (!egg)
        return NULL;
    if (team)
        team->team_size++;
    game->eggs->methods->push_back(game->eggs, egg);
    return egg;
}

/**
 * @brief Create a game event for an egg being laid.
 *
 * @param egg Pointer to the egg that was created.
 * @return Pointer to the event, or NULL on allocation failure.
 */
static game_event_t *create_egg_event(const egg_t *egg)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return NULL;
    event->type = EVENT_RESP_EGG_LAID;
    event->data.egg.player = egg->player;
    event->data.egg.team_name = egg->team_name;
    event->data.egg.x = egg->x;
    event->data.egg.y = egg->y;
    event->data.egg.egg_id = egg->id;
    return event;
}

/**
 * @brief Send a response event indicating a new egg was laid.
 *
 * @param game Pointer to the game instance.
 * @param egg Pointer to the egg that was laid.
 */
static void send_egg_laid_event(game_t *game, const egg_t *egg)
{
    game_event_t *event = create_egg_event(egg);

    if (!event)
        return;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, event);
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
    player_t *player = NULL;
    egg_t *egg = NULL;

    if (!game || !event)
        return;
    player = event->data.egg.player;
    if (!player)
        return;
    egg = add_egg_to_game(game, player);
    if (!egg)
        return;
    send_egg_laid_event(game, egg);
}
