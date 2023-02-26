#include "figure.h"
#include "widthheightparams.h"

void* allocate_memory_of_object_array(params_alocate_function_t params)
{
    void *buffer_pointer = malloc(params.one_object_mem_size * params.count);

    if (buffer_pointer == NULL)
        *(params.return_code) = ERROR_ALLOCATE_MEMORY;

    return buffer_pointer;
}

figure_t init_figure()
{
    err_t return_code = SUCCESS;
    figure_t figure;

    figure.edges_array = NULL;
    figure.points_array = NULL;
    figure.edges_array_length = 0;
    figure.point_array_lenght = 0;

    return figure;
}

bool check_wether_figure_is_free(figure_t *figure)
{
    return figure != NULL && figure->edges_array == NULL;
}

err_t free_figure_memory(figure_t *figure)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    free(figure->edges_array);
    free(figure->points_array);

    return return_code;
}

err_t check_figure_data_correctness(figure_t *figure)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; i < figure->edges_array_length; i++)
        if (figure->edges_array[i].start >= figure->point_array_lenght ||
                figure->edges_array[i].end >= figure->point_array_lenght)
            return_code = ERROR_INCORRECT_EDGE_INFO;

    return return_code;
}

static figure_configuration_t init_figure_configuration(width_height_params_t params,
                                                        double min_left, double max_bottom)
{
    figure_configuration_t config;

    config.object_params = params;
    config.min_bottum_cord = max_bottom;
    config.min_left_cord = min_left;

    return config;
}

figure_configuration_t get_figure_projection_width_height_params(figure_t figure)
{
    double max_right = 0, max_left = 0, max_bottom = 0, max_top = 0;

    if (figure.point_array_lenght > 0)
    {
        max_right = figure.points_array[0].x;
        max_left = 0;
        max_bottom = 0;
        max_top = figure.points_array[0].y;
    }

    for (size_t i = 1; i < figure.point_array_lenght &&
         figure.points_array != NULL; i++)
    {
        max_right = fmax(figure.points_array[i].x, max_right);
        max_left = fmin(figure.points_array[i].x, max_left);
        max_bottom = fmin(figure.points_array[i].y, max_bottom);
        max_top = fmax(figure.points_array[i].y, max_top);
    }

    double real_width = fabs(max_right - max_left) + 1;
    double real_height = fabs(max_top - max_bottom) + 1;
    width_height_params_t params = init_width_height_params(real_width, real_height);

    return init_figure_configuration(params, max_left, max_bottom);
}

err_t scale_figure(figure_t *figure, scale_coefficients_t *coefficients)
{
    if (figure == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
        return_code = scale_point_coords(&(figure->points_array[i]), &(figure->points_array[i]), coefficients);

    return return_code;
}

err_t move_figure(figure_t *figure, move_coefficients_t *coefficients)
{
    if (figure == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
        return_code = move_point_coords(&(figure->points_array[i]), &(figure->points_array[i]), coefficients);

    return return_code;
}

err_t rotate_figure(figure_t *figure, rotate_coefficients_t *coefficients)
{
    if (figure == NULL || figure->points_array == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
        return_code = turn_point_coords(&(figure->points_array[i]), coefficients);

    return return_code;
}
