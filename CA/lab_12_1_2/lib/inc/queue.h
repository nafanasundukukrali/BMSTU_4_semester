#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#define QUEUE_IS_FREE 0

#define ERROR_NO_DATA 32
#define ERROR_MEM_ALLOCATE 33

typedef struct list_t list_t;

struct list_t
{
    int value;
    list_t *next;    
};

typedef struct
{
    list_t *start;
    list_t *end;
    size_t size;
} list_queue_t;

list_t *init_new_element(const int value);

list_queue_t *init_list_queue();
int list_pop(list_queue_t *queue);
short list_push(list_queue_t *queue, int value);
void list_free_queue(list_queue_t *queue);

#endif
