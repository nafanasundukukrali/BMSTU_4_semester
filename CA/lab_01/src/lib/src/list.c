#include "../inc/list.h"

node_t *create_list_node()
{
    node_t *node = NULL;

    node = malloc(sizeof(node_t));

    if (node == NULL)
        return NULL;

    node->next = NULL;

    return node;
}

short insert_node_to_start(node_t **head, double data)
{
    node_t *node = create_list_node();

    if (node == NULL)
        return ERROR_MALLOC_DATA;

    node->data = data;
    
    
}

short insert_node_to_end(node_t **head,  double data)
{
    node_t *node = create_list_node();

    if (node == NULL)
        return ERROR_MALLOC_DATA;

    node->data = data;

    if (*head == NULL)
    {
        *head = node;
        return EXIT_SUCCESS;
    }

    node_t *buffer = *head;

    while (buffer != NULL && buffer->next != NULL)
        buffer = buffer->next;

    buffer->next = node;

    return EXIT_SUCCESS;
}

/*
short malloc_node(node_t **node)
{
    *node = NULL;
    *node = malloc(sizeof(node_t));

    if (*node == NULL)
        return ERROR_MALLOC_DATA;

    (*node)->next = NULL;

    return EXIT_SUCCESS;
}
*/

/*
node_t *find(node_t *head, void *data, int (*comparator)(void*, void *), size_t *steps)
{
    *steps = 0;

    while (head != NULL && comparator(head->data, data))
    {
        head = head->next;
        *steps += 1;
    }

    return head;
}
*/

double pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return -1;

    double buffer_data = (*head)->data;
    node_t *buffer_node = (*head)->next;

    free(*head);
    *head = buffer_node;

    return buffer_data;
}

/*
void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*))
{
    node_t *buffer_head = *head, *second_buffer;

    while (buffer_head != NULL && buffer_head->next != NULL)
    {
        second_buffer = buffer_head->next;

        while (second_buffer != NULL && !comparator(buffer_head->data, second_buffer->data))
        {
            second_buffer = second_buffer->next;
            free(buffer_head->next);
            buffer_head->next = second_buffer;
        }

        buffer_head = buffer_head->next;
    }
}
*/

/*
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (*head == NULL)
    {
        element->next = *head;
        *head = element;

        return;
    }

    node_t *buffer = *head;

    while (buffer->next != NULL && 
        comparator(element->data, buffer->next->data) > 0)
        buffer = buffer->next;

    if (comparator(buffer->data, element->data) > 0)
    {
        element->next = *head;
        *head = element;
    }
    else
    {
        element->next = buffer->next;
        buffer->next = element;
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *result = NULL, *buffer;

    while (head != NULL && comparator != NULL)
    {
        buffer = head->next;
        sorted_insert(&result, head, comparator);
        head = buffer;
    }

    return result;
}
*/

void free_list(node_t **head)
{
    while (*head != NULL)
        pop_front(head);
}
