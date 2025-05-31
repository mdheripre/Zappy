/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** config.h
*/

#ifndef CONFIG_H_
    #define CONFIG_H_

#include "dispatcher.h"
#include "list.h"

typedef struct config_s config_t;

typedef struct config_methods_s {
    void (*destroy)(struct config_s *self);
} config_methods_t;

struct config_s {
    int port;
    float frequency;
    int width;
    int height;
    int team_size;
    list_t *team_name;
    dispatcher_t *dispatcher;
    const config_methods_t *methods;
};

typedef struct parser_s {
    int index;
    int argc;
    char **argv;
    bool error;
    char *error_msg;
} parser_t;

config_t *config_create(int argc, char **argv);
void config_destroy(config_t *self);

/* Event */
void port_arg(void *ctx, void *event_data);
#endif /* CONFIG_H_ */
