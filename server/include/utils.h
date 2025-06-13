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
    #include <stddef.h>
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

typedef struct {
    int x;
    int y;
} vector2i_t;

typedef struct {
    int dx;
    int dy;
    char *buffer;
} query_t;

typedef struct {
    int ticks;
    const char *origin;
} tick_info_t;

typedef struct {
    char *buf;
    bool *first;
} write_ctx_t;

typedef struct {
    game_t *game;
    player_t *player;
    write_ctx_t writer;
} explore_ctx_t;

void console_log(log_level_t level, const char *format, ...);
void strip_linefeed(char *line);
long get_ms_time(void);
bool client_enqueue_command(client_t *client, const char *cmd, int ticks,
    game_t *game);
queued_command_t *client_peek_command(client_t *client);
bool client_dequeue_command(client_t *client, queued_command_t *out);
const char *event_type_name(game_event_type_t type);
player_t *find_player_by_id(game_t *game, int player_id);
int get_client_fd_by_player(server_t *server, player_t *player, int *index);
int get_client_index_by_player(server_t *server, player_t *player);
char *extract_command_name(const char *line, char *out, size_t size);
const char *extract_command_args(const char *line);
bool extract_command_arguments(const char *line, char *out, size_t out_size);
client_t *get_client_by_fd(server_t *server, int fd);
int get_client_index_by_player(server_t *server, player_t *player);
client_t *get_client_by_player(server_t *server, player_t *player,
    int *index);
client_t *get_gui_client(server_t *server);
#endif /* !UTILS_H_ */
