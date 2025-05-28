/*
** EPITECH PROJECT, 2025
** server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include <stdbool.h>
    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <unistd.h>
    #include <poll.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <sys/time.h>
    #include "client.h"
    #include "shared.h"
    #include "dispatcher.h"
    #include "game.h"
    #define MAX_CLIENTS 100
    #define TIMEOUT_MS 100
    #define BUFFER_COMMAND_SIZE 128


typedef struct server_s server_t;


typedef struct server_methods_s {
    bool (*constructor)(server_t *self);
    void (*run)(server_t *self);
    void (*destroy)(server_t *self);
    void (*setup_poll)(server_t *self, struct pollfd *fds, nfds_t *nfds);
    void (*handle_poll)(server_t *self, struct pollfd *fds);
    void (*accept_client)(server_t *self);
    void (*remove_client)(server_t *self, int index);
    float (*get_command_delay)(server_t *self, const char *command);
} server_methods_t;

struct server_s {
    int socket_fd;
    struct sockaddr_in address;
    int port;
    float frequency;
    client_t clients[MAX_CLIENTS];
    int client_count;
    dispatcher_t *dispatcher;
    const server_methods_t *vtable;
    game_t *game;
};


bool init_socket(server_t *self);
server_t *server_create(int port, int width, int height, float frequency);
bool server_init(server_t *server, int port);
void remove_client(server_t *self, int index);
void accept_client(server_t *self);
void setup_server_poll(server_t *self, struct pollfd *fds, nfds_t *nfds);
void handle_server_poll(server_t *self, struct pollfd *fds);
void server_destroy(server_t *self);
void run_server(server_t *self);

/* Command */
void command_process_all(server_t *server, float delta_time);
void command_manager_register_all(server_t *server);
void handle_command_forward(void *ctx, void *data);
float get_command_delay(server_t *server, const char *command);
void command_process_identify(server_t *server);

/* Event */
void on_client_connected(void *ctx, void *event_data);
void on_client_identify(void *ctx, void *data);
void on_event_not_found(dispatcher_t *self, const char *event, void *data);

/* Game */
void dispatch_game_events(server_t *server);
#endif /* SERVER_H_ */
