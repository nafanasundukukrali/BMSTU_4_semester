#include "edge.h"
#include <cstddef>

edge_t init_edge(const size_t start, const size_t end)
{
    edge_t edge;

    edge.start = start;
    edge.end = end;

    return edge;
}

err_t get_edge_points_indeces(size_t *start_value, size_t *end_value, edge_t *edge)
{
    if (start_value == NULL || end_value == NULL || edge == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *start_value = edge->start;
    *end_value = edge->end;

    return SUCCESS;
}

static err_t read_edge_data_from_file(void *edge, FILE *file)
{
    if (edge == NULL || file == NULL || feof(file) || ferror(file))
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;
    size_t start, end;

    return_code = read_size_t_number_from_file(&start, file);

    if (return_code == SUCCESS)
    {
        return_code = read_size_t_number_from_file(&end, file);

        if (return_code == SUCCESS)
        {
            edge_t *edge_pointer = (edge_t *)edge;
            *edge_pointer = init_edge(start, end);
        }
    }

    return return_code;
}

static err_t malloc_edge_array(edge_t **array_pointer, const size_t malloc_size)
{
    edge_t *buffer = NULL;
    err_t return_code = SUCCESS;

    buffer = (edge_t *) malloc(malloc_size * sizeof(edge_t));

    if (buffer == NULL)
    {
        return_code = ERROR_ALLOCATE_MEMORY;
    }
    else
    {
        *array_pointer = buffer;
    }

    return return_code;
}


static err_t read_array_data_from_file(edge_t *array, FILE *file, const size_t array_length)
{
    if (array == NULL || file == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    for (size_t i = 0; i < array_length && return_code == SUCCESS; i += 1)
    {
        return_code = read_edge_data_from_file(&(array[i]), file);
    }

    return return_code;
}

err_t read_information_about_edges_from_file(edge_t **edge_array, size_t *edge_array_size, FILE *file)
{
    if (file == NULL || edge_array == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    return_code = read_size_t_number_from_file(edge_array_size, file);

    if (return_code == SUCCESS)
    {
        return_code = malloc_edge_array(edge_array, *edge_array_size);

        if (return_code == SUCCESS)
        {
            return_code = read_array_data_from_file(*edge_array, file, *edge_array_size);

            if (return_code != SUCCESS)
            {
                free(*edge_array);
            }
        }
    }

    return return_code;
}
