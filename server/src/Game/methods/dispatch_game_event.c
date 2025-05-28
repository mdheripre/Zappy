/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatch_game_event
*/


#include "game.h"
#include "server.h"
#include "dispatcher.h"
#include "client.h"
#include "shared.h"

static void emit_to_all_gui(server_t *server, const char *message)
{
    for (int i = 0; i < server->client_count; i++) {
        client_t *client = &server->clients[i];
        if (client->type == CLIENT_GUI)
            dispatcher_emit(server->dispatcher, client, message);
    }
}

void dispatch_game_events(server_t *server)
{
    game_event_t *event = NULL;
    char buffer[256] = {0};

    while ((event = server->game->methods->pop_event(server->game))) {
        switch (event->type) {
            case GAME_EVENT_PLAYER_DIED:
                snprintf(buffer, sizeof(buffer), "pdi #%d\n",
                    event->data.died.player_id);
                emit_to_all_gui(server, buffer);
                break;
            default:
                break;
        }
        free(event);
    }
}
