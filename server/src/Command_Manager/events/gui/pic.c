/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pic
*/

#include "command_manager.h"
#include "shared.h"
#include "server.h"
#include "client.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/


static void build_pic_message(char *buffer, size_t buffer_size,
    game_event_t *event)
{
    list_t *participants = event->data.incantation.participants;
    player_t *p = NULL;
    size_t offset = 0;

    offset += snprintf(buffer + offset, buffer_size - offset,
        "pic %d %d %d", event->data.incantation.x,
        event->data.incantation.y,
        ((player_t *)participants->head->data)->level);
    for (list_node_t *n = participants->head; n; n = n->next) {
        p = n->data;
        offset += snprintf(buffer + offset, buffer_size - offset,
            " #%d", p->id);
    }
    snprintf(buffer + offset, buffer_size - offset, "\n");
}

void handle_gui_pic(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *gui = server->gui;
    char buffer[BUFFER_SIZE] = {0};

    if (!server || !event || !gui)
        return;
    build_pic_message(buffer, sizeof(buffer), event);
    dprintf(gui->fd, "%s", buffer);
}
