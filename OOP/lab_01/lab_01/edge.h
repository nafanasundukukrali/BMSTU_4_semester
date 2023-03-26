#ifndef EDGE_H
#define EDGE_H

#include <cstdlib>
#include "error.h"
#include "filebasemanipulations.h"

typedef struct
{
    size_t start;
    size_t end;
} edge_t;

edge_t init_edge(const size_t start, const size_t end);
err_t get_edge_points_indeces(size_t *start_value, size_t *end_value, edge_t *edge);
err_t read_information_about_edges_from_file(edge_t **edge_array, size_t *edge_array_size, FILE *file);

#endif // EDGE_H
