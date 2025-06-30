/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** command_manager_process_response
*/

#include "command_manager.h"
#include "game.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                       PROCESS RESPONSE                                   */
/*                                                                          */
/****************************************************************************/

static const gui_event_t gui_event_map[] = {
    { GUI_CMD_PMV, EVENT_GUI_PMV },
    { GUI_CMD_PFK, EVENT_GUI_PFK },
    { GUI_CMD_PEJ, EVENT_GUI_PEJ },
    { GUI_CMD_NONE, 0 }
};

static void process_game_events(command_manager_t *self, game_t *game)
{
    game_event_t *event = NULL;

    if (!self || !self->dispatcher || !game)
        return;
    for (event = game->server_event_queue->methods->pop_front(
        game->server_event_queue); event != NULL;
        event = game->server_event_queue->methods->pop_front(
            game->server_event_queue)) {
        EMIT(self->dispatcher, event->type, event);
        free(event);
    }
}

static void emit_gui_event_for_command(command_manager_t *self,
    client_t *client, queued_command_t *cmd)
{
    if (!cmd || cmd->gui_check == GUI_CMD_NONE)
        return;
    for (int i = 0; gui_event_map[i].type != GUI_CMD_NONE; i++) {
        if (cmd->gui_check == gui_event_map[i].type) {
            EMIT(self->dispatcher, gui_event_map[i].event, client->player);
            cmd->gui_check = GUI_CMD_NONE;
            break;
        }
    }
}

static void process_gui_responses(command_manager_t *self, server_t *server)
{
    client_t *client = NULL;
    queued_command_t *cmd = NULL;

    if (!self || !self->dispatcher || !server || !server->clients)
        return;
    for (list_node_t *n = server->clients->head; n; n = n->next) {
        client = n->data;
        if (!client)
            continue;
        cmd = client_peek_command(client);
        emit_gui_event_for_command(self, client, cmd);
    }
}

void process_responses(command_manager_t *self, game_t *game, server_t *server)
{
    process_game_events(self, game);
    process_gui_responses(self, server);
}
