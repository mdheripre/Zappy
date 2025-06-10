/*
** EPITECH PROJECT, 2025
** server
** File description:
** Command_Manager
*/

#ifndef COMMAND_MANAGER_H_
    #define COMMAND_MANAGER_H_
    #include "server.h"
    #include "utils.h"


typedef struct command_manager_s command_manager_t;
typedef struct command_manager_methods_s command_manager_methods_t;
typedef struct server_s server_t;

struct command_manager_methods_s {
    void (*register_all)(command_manager_t *self, server_t *server);
    void (*process_identify)(command_manager_t *self, server_t *server);
    void (*process_all)(command_manager_t *self, server_t *server,
        float delta);
    void (*process_responses)(command_manager_t *self, game_t *game);
};

struct command_manager_s {
    const command_manager_methods_t *methods;
    dispatcher_t *dispatcher;
};

/* Object */
command_manager_t *command_manager_create(void);
void command_manager_destroy(command_manager_t *self);
void register_all(command_manager_t *self, server_t *server);
void process_identify(command_manager_t *self, server_t *server);
void process_all(command_manager_t *self, server_t *server, float delta);
void on_command_not_found(dispatcher_t *self, const char *event, void *data);
void process_responses(command_manager_t *self, game_t *game);

/* Handlers */
void handle_command_forward(void *ctx, void *data);
void handle_command_right(void *ctx, void *data);
void handle_command_left(void *ctx, void *data);
void handle_command_connect_nbr(void *ctx, void *data);
void handle_command_incantation(void *ctx, void *data);
void handle_command_look(void *ctx, void *data);
void handle_command_inventory(void *ctx, void *data);
void handle_command_take(void *ctx, void *data);
void handle_command_drop(void *ctx, void *data);
void handle_command_eject(void *ctx, void *data);
void handle_command_fork(void *ctx, void *data);
void handle_command_broadcast(void *ctx, void *data);

/* GUI */
void handle_command_gui_msz(void *ctx, void *data);
void handle_command_gui_sgt(void *ctx, void *data);
void handle_command_gui_tna(void *ctx, void *data);
void handle_command_gui_bct(void *ctx, void *data);
void handle_command_gui_mct(void *ctx, void *data);

/* Responses */
void on_response_player_moved(void *ctx, void *data);
void on_response_player_died(void *ctx, void *data);
void on_response_connect_nbr(void *ctx, void *data);
void on_response_look(void *ctx, void *data);
void on_response_inventory(void *ctx, void *data);

#endif /* !COMMAND_MANAGER_H_ */
