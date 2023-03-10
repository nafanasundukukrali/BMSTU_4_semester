#include "fileio.h"

err_t open_file_by_path(char *filePath, FILE **file)
{
    if (filePath == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    FILE *buffer_file = NULL;

    buffer_file = fopen(filePath, "r");

    if (buffer_file == NULL || ferror(buffer_file))
        return_code = ERROR_OPEN_FILE;

    if (feof(buffer_file))
        return_code = ERROR_NO_DATA;

    if (return_code == SUCCESS)
        *file = buffer_file;
    else if (buffer_file != NULL)
        fclose(buffer_file);

    return return_code;
}

typedef struct
{
    void *array;
    FILE *file;
    err_t (*read_one_element_function) (void *object, FILE *);
    size_t array_length;
    size_t size_of_one_element;
} params_of_array_read_func_t;

static err_t read_array_data_from_file(params_of_array_read_func_t params)
{
    if (params.array == NULL ||
            params.file == NULL || params.read_one_element_function == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    char *buffer_array = (char *)(params.array);

    for (size_t i = 0; i < params.array_length * params.size_of_one_element &&
         return_code == SUCCESS; i += params.size_of_one_element)
        return_code = params.read_one_element_function((void *)(buffer_array + i),
                                                        params.file);

    return return_code;
}

static err_t read_size_t_number_from_file(FILE *file, size_t *number)
{
    if (file == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    long long buffer_count;

    if (fscanf(file, "%lld", &buffer_count) != ONE_CORRECT_READ_DATA)
        return_code = ERROR_READ_DATA;

    if (return_code == SUCCESS)
        *number = (size_t)buffer_count;

    return return_code;
}

static err_t read_point_data_from_file(void *point, FILE *file)
{
    if (point == NULL || file == NULL || feof(file) || ferror(file))
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    double x, y, z;

    int result_of_reading = fscanf(file, "%lf%lf%lf", &x, &y, &z);

    if (result_of_reading != READING_COORDS_SUCCESS_COUNT)
        return_code = ERROR_READ_DATA;

    if (return_code == SUCCESS)
    {
        point_t *point_pointer = (point_t *)point;
        *point_pointer = init_point(x, y, z);
    }

    return return_code;
}

static err_t read_edge_data_from_file(void *edge, FILE *file)
{
    if (edge == NULL || file == NULL || feof(file) || ferror(file))
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    size_t start, end;

    return_code = read_size_t_number_from_file(file, &start);

    if (return_code == SUCCESS)
        return_code = read_size_t_number_from_file(file, &end);

    if (return_code == SUCCESS)
    {
        edge_t *edge_pointer = (edge_t *)edge;
        *edge_pointer = init_edge(start, end);
    }

    return return_code;
}

static err_t read_information_about_points_from_file(figure_t *buffer_figure, FILE *file)
{
    if (file == NULL || buffer_figure == NULL || buffer_figure->points_array != NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    size_t array_size;
    point_t *buffer_point_array;

    return_code = read_size_t_number_from_file(file, &array_size);

    if (return_code == SUCCESS)
        buffer_point_array = (point_t *)allocate_memory_of_object_array({&return_code, sizeof(point_t), array_size});

    if (return_code == SUCCESS)
        return_code = read_array_data_from_file({(void *)buffer_point_array, file, read_point_data_from_file,
                                                    array_size, sizeof(point_t)});

    if (return_code == SUCCESS)
        return_code = set_figure_points_count(buffer_figure, array_size);

    if (return_code == SUCCESS)
        return_code = set_figure_points_array(buffer_figure, buffer_point_array);

    return return_code;
}

static err_t read_information_about_edges_from_file(figure_t *buffer_figure, FILE *file)
{
    if (file == NULL || buffer_figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    size_t array_size;
    edge_t *buffer_edge_array;

    return_code = read_size_t_number_from_file(file, &array_size);

    if (return_code == SUCCESS)
        buffer_edge_array = (edge_t *)allocate_memory_of_object_array({&return_code, sizeof(edge_t),
                                                                                array_size});

    if (return_code == SUCCESS)
        return_code = read_array_data_from_file({(void *)buffer_edge_array, file, read_edge_data_from_file,
                                                    array_size, sizeof(edge_t)});

    if (return_code == SUCCESS)
        return_code = set_figure_edges_count(buffer_figure, array_size);

    if (return_code == SUCCESS)
        return_code = set_figure_edges_array(buffer_figure, buffer_edge_array);

    return return_code;
}

err_t read_data_from_file(FILE *file, figure_t *figure)
{
    if (file == NULL || figure == NULL || ferror(file) || feof(file))
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;
    figure_t buffer_figure = init_figure();

    return_code = read_information_about_points_from_file(&buffer_figure, file);

    if (return_code == SUCCESS)
        return_code = read_information_about_edges_from_file(&buffer_figure, file);

    if (return_code != SUCCESS)
        free_figure_memory(&buffer_figure);
    else
        *figure = buffer_figure;

    return return_code;
}
