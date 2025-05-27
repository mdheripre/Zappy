/*
** EPITECH PROJECT, 2025
** server
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include <stdbool.h>
    #define CLIENT_BUFFER_SIZE 1024
    #define MAX_COMMANDS 10

typedef enum client_type_e {
    CLIENT_UNDEFINED = 0,
    CLIENT_IA,
    CLIENT_GUI
} client_type_t;

typedef struct queued_command_s {
    char content[CLIENT_BUFFER_SIZE];
    float time_remaining;
} queued_command_t;


typedef struct client_s {
    int fd;
    bool connected;
    client_type_t type;
    char read_buffer[CLIENT_BUFFER_SIZE];
    queued_command_t commands[MAX_COMMANDS];
    int command_head;
    int command_tail;
    int command_count;
    size_t buffer_len;
} client_t;



bool client_enqueue_command(client_t *client,
    const char *cmd, float delay);
bool client_dequeue_command(client_t *client, queued_command_t *out);
queued_command_t *client_peek_command(client_t *client);
#endif /* CLIENT_H_ */
