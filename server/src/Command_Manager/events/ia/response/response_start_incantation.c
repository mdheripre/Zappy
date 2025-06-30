/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_start_incantation
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
 * @brief Send a "ko" message to the first participant of a failed incantation.
 *
 * @param participants List of incantation participants.
 */
static void send_ko_to_first_participant(list_t *participants)
{
    player_t *player = NULL;
    client_t *client = NULL;

    if (!participants || !participants->head)
        return;
    player = participants->head->data;
    client = player->client;
    if (client)
        dprintf(client->fd, "ko\n");
}

/**
 * @brief Notify all incantation participants that the ritual is starting.
 *
 * Sends "elevation underway" and marks them as stuck.
 *
 * @param participants List of players participating in the incantation.
 */
static void notify_participants_elevation(list_t *participants)
{
    player_t *player = NULL;
    client_t *client = NULL;

    for (list_node_t *n = participants->head; n; n = n->next) {
        player = n->data;
        client = player->client;
        if (!client)
            continue;
        client->stuck = true;
        dprintf(client->fd, "Elevation underway\n");
    }
}

/**
 * @brief Handle the start of an incantation and notify participants.
 *
 * Sends "ko" if the incantation failed, otherwise notifies participants
 * and emits a GUI PIC event.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the incantation start event.
 */
void on_response_start_incantation(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    list_t *participants = event->data.incantation.participants;

    if (!server || !event)
        return;
    if (!event->data.incantation.success) {
        send_ko_to_first_participant(participants);
        return;
    }
    notify_participants_elevation(participants);
    EMIT(server->command_manager->dispatcher, EVENT_GUI_PIC, event);
}
