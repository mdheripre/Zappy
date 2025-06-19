/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_end_incantation
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Send the result of an incantation to a player.
 *
 * Sends "current level: N" on success, or "ko" on failure.
 * Also unstucks the player.
 *
 * @param server Pointer to the server instance.
 * @param event Pointer to the incantation result event.
 * @param player Pointer to the affected player.
 */
static void send_incantation_result(server_t *server,
    game_event_t *event, player_t *player)
{
    client_t *client = get_client_by_player(server, player, NULL);
    int fd = -1;

    if (!client)
        return;
    client->stuck = false;
    fd = get_client_fd_by_player(server, player, NULL);
    if (fd != -1) {
        if (event->data.incantation.success) {
            dprintf(fd, "current level: %d\n", player->level);
            EMIT(server->command_manager->dispatcher, "gui_plv",
                &player->id);
        } else
            dprintf(fd, "ko\n");
    }
}

/**
 * @brief Reschedule the next command of a player after an incantation.
 *
 * Updates the tick tracking of the next command if needed.
 *
 * @param server Pointer to the server instance.
 * @param player Pointer to the player.
 */
static void replan_next_command(server_t *server, player_t *player)
{
    client_t *client = get_client_by_player(server, player, NULL);
    queued_command_t *next = NULL;

    if (!client)
        return;
    next = client_peek_command(client);
    if (next && next->ticks_remaining > 0)
        next->last_tick_checked = server->game->tick_counter + 1;
}

/**
 * @brief Handle the end of an incantation for all participants.
 *
 * Sends result messages and replans next command for each.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the incantation end event.
 */
void on_response_end_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = NULL;

    if (!server || !event)
        return;
    for (list_node_t *n = event->data.incantation.participants->head;
        n; n = n->next) {
        player = n->data;
        send_incantation_result(server, event, player);
        replan_next_command(server, player);
    }
    EMIT(server->command_manager->dispatcher, "gui_pie", event);
}
