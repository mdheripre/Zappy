/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** poll_manager
*/

#ifndef POLL_MANAGER_H_
    #define POLL_MANAGER_H_
    #include "server.h"

typedef struct poll_manager_s poll_manager_t;

typedef struct poll_manager_methods_s {
    bool (*resize)(poll_manager_t *, size_t);
    struct pollfd *(*get_fds)(poll_manager_t *, nfds_t *);
    void (*destroy)(poll_manager_t *);
} poll_manager_methods_t;

typedef struct poll_manager_s {
    struct pollfd *fds;
    nfds_t nfds;
    size_t capacity;
    poll_manager_methods_t methods;
} poll_manager_t;

poll_manager_t *poll_manager_create(size_t initial_size);
void poll_manager_destroy(poll_manager_t *self);
bool poll_manager_resize(poll_manager_t *self, size_t new_size);
struct pollfd *poll_manager_get_fds(poll_manager_t *self, nfds_t *out_nfds);
#endif /* !POLL_MANAGER_H_ */
