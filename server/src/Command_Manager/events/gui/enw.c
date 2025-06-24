/*
** EPITECH PROJECT, 2025
** server
** File description:
** mct
*/

#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Formats the ENW (egg new) event message for the GUI.
 *
 * @param buffer The buffer to write the message into.
 * @param size The size of the buffer.
 * @param event The game event containing egg information.
 */
static void format_enw_message(char *buffer, size_t size,
    const game_event_t *event)
{
    snprintf(buffer, size, "enw #%d #%d %d %d\n",
        event->data.egg.egg_id,
        event->data.egg.player ? event->data.egg.player->id : -1,
        event->data.egg.x, event->data.egg.y);
}

/**
 * @brief Handles the ENW event for the GUI by sending the message directly.
 *
 * @param ctx The server context.
 * @param data The event data.
 */
void handle_gui_enw(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    char buffer[BUFFER_SIZE] = {0};

    if (!server || !event || !server->gui)
        return;
    format_enw_message(buffer, sizeof(buffer), event);
    dprintf(server->gui->fd, "%s", buffer);
}
