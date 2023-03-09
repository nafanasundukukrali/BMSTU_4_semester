#include "edge.h"
#include <cstddef>

edge_t init_edge(size_t start, const size_t end)
{
    edge_t edge;

    edge.start = start;
    edge.end = end;

    return edge;
}

err_t get_edge_start(edge_t *edge, size_t *dst_value)
{
    if (edge == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = edge->start;

    return SUCCESS;
}

err_t get_edge_end(edge_t *edge, size_t *dst_value)
{
    if (edge == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = edge->end;

    return SUCCESS;
}
