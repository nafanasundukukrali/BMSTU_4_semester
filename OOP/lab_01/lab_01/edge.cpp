#include "edge.h"
#include <cstddef>

edge_t init_edge(size_t start, size_t end)
{
    edge_t edge;

    edge.start = start;
    edge.end = end;

    return edge;
}

