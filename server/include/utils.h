/*
** EPITECH PROJECT, 2025
** server
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_
    #include <stdio.h>
    #include <stdarg.h>
    #include <time.h>
    #include "server.h"
    #include "client.h"
    #define COLOR_INFO "\033[36m"
    #define COLOR_SUCCESS "\033[32m"
    #define COLOR_WARNING "\033[33m"
    #define COLOR_ERROR "\033[31m"
    #define COLOR_RESET "\033[0m"


typedef struct client_s client_t;
typedef struct queued_command_s queued_command_t;
typedef enum log_level_e {
    LOG_INFO,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR
} log_level_t;

void console_log(log_level_t level, const char *format, ...);
void strip_linefeed(char *line);
long get_ms_time(void);
bool client_enqueue_command(client_t *client,
    const char *cmd, float delay);
bool client_dequeue_command(client_t *client, queued_command_t *out);
queued_command_t *client_peek_command(client_t *client);
const char *event_type_name(game_event_type_t type);
player_t *find_player_by_id(game_t *game, int player_id);
int get_client_fd_by_player(server_t *server, player_t *player, int *index);
int get_client_index_by_player(server_t *server, player_t *player);
#endif /* !UTILS_H_ */
