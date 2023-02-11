#include "queue.h"

list_queue_t *init_list_queue()
{
    list_queue_t *queue = NULL;
    queue = malloc(sizeof(list_queue_t));

    if (queue == NULL)
        return NULL;

    queue->start = NULL;
    queue->end = NULL;
    queue->size = 0;

    return queue; 
}

list_t *init_new_element(const int value)
{
    list_t *node = NULL;
    node = malloc(sizeof(list_t));

    if (node == NULL)
        return NULL;
    
    node->next = NULL;
    node->value = value;

    return node;
}

int list_pop(list_queue_t *queue)
{
    if (queue == NULL || queue->start == NULL)
        return 0;

    list_t *buffer = queue->start->next;

    if (queue->start == queue->end)
        queue->end = NULL;

    int buffer_value = queue->start->value;
    free(queue->start);
    queue->start = buffer;
    queue->size--;

    return buffer_value;
}

short list_push(list_queue_t *queue, int value)
{
    if (queue == NULL)
        return ERROR_NO_DATA;

    list_t *node = init_new_element(value);

    if (node == NULL)
        return ERROR_MEM_ALLOCATE;

    if (queue->end != NULL)
        queue->end->next = node;

    queue->end = node;
    queue->size++;

    if (queue->start == NULL)
       queue->start = queue->end;

    return EXIT_SUCCESS; 
}

void list_free_queue(list_queue_t *queue)
{
    while (queue != NULL && queue->start != NULL)
        list_pop(queue);

    free(queue);
}
