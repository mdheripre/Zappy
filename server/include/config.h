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
    bool (*parse_args)(int argc, char **argv, config_t *self);
    bool (*is_int)(char *arg);
    bool (*str_are_equals)(void *data1, void *data2);
    bool (*is_float)(char *arg);
    void (*help_message)(void);
} config_methods_t;

struct config_s {
    int port;
    float frequency;
    int width;
    int height;
    int team_size;
    list_t *team_name;
    dispatcher_t *dispatcher;
    bool exit;
    const config_methods_t *methods;
};

typedef struct parser_s {
    int index;
    int argc;
    char **argv;
    bool error;
    char *error_msg;
    bool free;
} parser_t;

config_t *config_create(void);
void config_destroy(config_t *self);

/* Methods */
bool parse_args(int argc, char **argv, config_t *config);
bool is_int(char *arg);
bool is_float(char *arg);
bool str_are_equals(void *data1, void *data2);
void help_message(void);

/* Event */
void invalid_arg(dispatcher_t *self, const char *event_data, void *data);
void port_arg(void *ctx, void *event_data);
void width_arg(void *ctx, void *event_data);
void height_arg(void *ctx, void *event_data);
void team_name_arg(void *ctx, void *event_data);
void team_size_arg(void *ctx, void *event_data);
void frequency_arg(void *ctx, void *event_data);
void help_arg(void *ctx, void *);
#endif /* CONFIG_H_ */
