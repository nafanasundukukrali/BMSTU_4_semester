#ifndef EDGE_H
#define EDGE_H

#include <cstdlib>
#include "error.h"

typedef struct
{
    size_t start;
    size_t end;
} edge_t;

edge_t init_edge(size_t start, const size_t end);
err_t get_edge_start(edge_t *edge, size_t *dst_value);
err_t get_edge_end(edge_t *edge, size_t *dst_value);

#endif // EDGE_H
