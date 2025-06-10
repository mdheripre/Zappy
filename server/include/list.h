/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** list
*/


#ifndef LIST_H_
    #define LIST_H_

    #include <stdlib.h>
    #include <stdbool.h>

typedef struct list_node_s {
    void *data;
    struct list_node_s *next;
} list_node_t;

typedef struct list_s list_t;

typedef struct list_methods_s {
    void (*destroy)(list_t *self);
    void (*clear)(list_t *self);
    void (*push_back)(list_t *self, void *data);
    void *(*pop_front)(list_t *self);
    int (*size)(const list_t *self);
    bool (*contain)(list_t *self, void *data, bool (*compare)(void *, void *));
    void (*remove)(list_t *self, void *target);
    void *(*consume)(list_t *self, bool (*match)(void *, void *), void *data);
    void *(*front)(const list_t *self);
} list_methods_t;

struct list_s {
    list_node_t *head;
    list_node_t *tail;
    int size;
    void (*free_fn)(void *);
    const list_methods_t *methods;
};

list_t *list_create(void (*free_fn)(void *));
void list_destroy(list_t *self);
void list_clear(list_t *self);
void list_push_back(list_t *self, void *data);
void *list_pop_front(list_t *self);
int list_size(const list_t *self);
bool list_contain(list_t *self, void *data, bool (*compare)(void *, void *));
void list_remove(list_t *self, void *target);
void *list_consume(list_t *self, bool (*match)(void *, void *), void *data);
void *list_peek_front(const list_t *self);
#endif /* !LIST_H_ */
