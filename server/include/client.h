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

typedef struct client_s client_t;

typedef struct client_s {
    int fd;
    bool connected;
    char read_buffer[CLIENT_BUFFER_SIZE];
    size_t buffer_len;
} client_t;

#endif /* CLIENT_H_ */
