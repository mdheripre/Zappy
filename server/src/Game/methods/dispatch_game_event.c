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

const char *event_type_name(game_event_type_t type)
{
    for (size_t i = 0;
        i < sizeof(EVENT_TYPE_MAP) / sizeof(EVENT_TYPE_MAP[0]); i++) {
        if (EVENT_TYPE_MAP[i].type == type)
            return EVENT_TYPE_MAP[i].name;
    }
    return "UNKNOWN";
}

void emit_to_all_gui(server_t *server, const char *message)
{
    response_payload_t *payload = NULL;
    client_t *client = NULL;

    if (!server || !message)
        return;
    for (int i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (client->type != CLIENT_GUI)
            continue;
        payload = malloc(sizeof(response_payload_t));
        if (!payload)
            continue;
        payload->client = client;
        payload->message = message;
        EMIT(server->dispatcher, "send_response", payload);
    }
}

void dispatch_game_events(server_t *server)
{
    game_event_t *event = NULL;
    const char *event_name = NULL;

    if (!server || !server->game || !server->game->dispatcher)
        return;
    event = server->game->methods->pop_event(server->game);
    while (event) {
        event_name = event_type_name(event->type);
        EMIT(server->game->dispatcher, event_name, event);
        free(event);
        event = server->game->methods->pop_event(server->game);
    }
}
