#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "errors.h"

typedef struct node_t node_t;

struct node_t 
{
    double node;
    node_t *next;
};

short insert_node_to_list(node_t **head, char *word);
node_t *find(node_t *head, void *data, int (*comparator)(void*, void *), size_t *steps);
void *pop_front(node_t **head);
//void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));
//void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*));
//node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void free_list(node_t **head);

#endif
