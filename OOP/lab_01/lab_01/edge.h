#ifndef EDGE_H
#define EDGE_H

#include <cstdlib>

typedef struct
{
    size_t start;
    size_t end;
} edge_t;

edge_t init_edge(size_t start, size_t end);

#endif // EDGE_H
