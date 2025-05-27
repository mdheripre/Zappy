/*
** EPITECH PROJECT, 2025
** server
** File description:
** forward
*/

#include "server.h"
#include "utils.h"


/****************************************************************************/
/*                                                                          */
/*                        COMMAND PRIVATE                                   */
/*                                                                          */
/****************************************************************************/

void handle_command_forward(void *ctx, void *data)
{
    client_t *client = data;

    (void)ctx;
    console_log(LOG_INFO, "Handling command: Forward (fd=%d)", client->fd);
    write(client->fd, "ok\n", 3);
}
