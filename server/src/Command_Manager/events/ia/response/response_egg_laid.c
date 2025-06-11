/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_egg_laid
*/

#include "game.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_egg_laid(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;

    if (!server || !event)
        return;
    printf("fin\n");
}
