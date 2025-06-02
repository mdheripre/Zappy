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

/* Handlers */
void handle_command_forward(void *ctx, void *data);
void handle_command_gui_msz(void *ctx, void *data);
void handle_command_gui_sgt(void *ctx, void *data);
void handle_command_gui_tna(void *ctx, void *data);
void handle_command_gui_bct(void *ctx, void *data);
void handle_command_gui_mct(void *ctx, void *data);

#endif /* !COMMAND_MANAGER_H_ */
