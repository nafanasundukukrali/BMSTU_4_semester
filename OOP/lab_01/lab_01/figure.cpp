#include "figure.h"
#include "objectsizeparams.h"

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

err_t get_point_info_by_index(point_t **dst_point, figure_t *figure, const size_t index)
{
    if (figure == NULL || index > figure->point_array_lenght)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *dst_point = &(figure->points_array[index]);

    return SUCCESS;
}

bool check_wether_figure_is_free(figure_t *figure)
{
    return figure != NULL && (figure->edges_array == NULL || figure->points_array == NULL);
}

err_t free_figure_memory(figure_t *figure)
{
    if (figure == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    free(figure->edges_array);
    free(figure->points_array);

    return return_code;
}

err_t check_figure_correctness(figure_t *figure)
{
    if (figure == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    for (size_t i = 0; i < figure->edges_array_length && return_code == SUCCESS; i++)
    {
        size_t start, end;

        return_code = get_edge_points_indeces(&start, &end, &(figure->edges_array[i]));

        if (return_code == SUCCESS &&
                (start >= figure->point_array_lenght ||
                end >= figure->point_array_lenght))
        {
            return_code = ERROR_INCORRECT_EDGE_INFO;
        }
    }

    return return_code;
}


err_t scale_figure(figure_t *figure, scale_coefficients_t *coefficients)
{
    if (figure == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
    {
        return_code = scale_point_coords(&(figure->points_array[i]), coefficients);
    }

    return return_code;
}

err_t move_figure(figure_t *figure, move_coefficients_t *coefficients)
{
    if (figure == NULL || coefficients == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
    {
        return_code = move_point_coords(&(figure->points_array[i]), coefficients);
    }

    return return_code;
}

err_t rotate_figure(figure_t *figure, rotate_coefficients_t *coefficients)
{
    if (figure == NULL || figure->points_array == NULL || coefficients == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    for (size_t i = 0; return_code == SUCCESS && i < figure->point_array_lenght; i++)
    {
        return_code = rotate_point_coords(&(figure->points_array[i]), coefficients);
    }

    return return_code;
}

err_t get_figure_edges_count(size_t *dst_value, figure_t *figure)
{
    if (figure == NULL || dst_value == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *dst_value = figure->edges_array_length;

    return SUCCESS;
}

err_t get_figure_edge_by_index(edge_t **edge, figure_t *figure, const size_t index)
{
    if (figure == NULL || edge == NULL || index > figure->edges_array_length)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *edge = &(figure->edges_array[index]);

    return SUCCESS;
}

err_t get_figure_point_by_index(point_t **point, figure_t *figure, const size_t index)
{
    if (figure == NULL || point == NULL || index > figure->point_array_lenght)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *point = &(figure->points_array[index]);

    return SUCCESS;
}

err_t set_figure_points_information(figure_t *figure, point_t *array_pointer, const size_t array_length)
{
    if (figure == NULL || array_pointer == NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure->points_array = array_pointer;
    figure->point_array_lenght = array_length;

    return SUCCESS;
}

err_t set_figure_edges_information(figure_t *figure, edge_t *array_pointer, const size_t array_length)
{
    if (figure == NULL || array_pointer == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    figure->edges_array = array_pointer;
    figure->edges_array_length = array_length;

    return SUCCESS;
}

typedef struct
{
    double max_bottom;
    double max_right;
    double max_left;
    double max_top;
} max_figure_params_t;

max_figure_params_t init_max_figure_params()
{
    max_figure_params_t params;

    params.max_bottom = 0;
    params.max_left = 0;
    params.max_right = 0;
    params.max_top = 0;

    return params;
}

static err_t get_figure_max_params(max_figure_params_t *params,  figure_t *figure)
{
    if (figure == NULL || check_wether_figure_is_free(figure) || params == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    double buffer_x = 0, buffer_y = 0;

    err_t return_code = SUCCESS;

    return_code = get_drawing_cords_of_point(&buffer_x, &buffer_y, &(figure->points_array[0]));

    if (return_code == SUCCESS)
    {
        params->max_right = buffer_x, params->max_top = buffer_y;
    }

    for (size_t i = 1; return_code == SUCCESS && i < figure->point_array_lenght; i++)
    {
        return_code = get_drawing_cords_of_point(&buffer_x, &buffer_y, &(figure->points_array[0]));

        if (return_code == SUCCESS)
        {
            params->max_right = fmax(buffer_x, params->max_right), params->max_left = fmin(buffer_x, params->max_left);
            params->max_bottom = fmin(buffer_y, params->max_bottom), params->max_top = fmax(buffer_y, params->max_top);
        }
    }

    return return_code;
}

typedef struct
{
    double min_left_cord;
    double min_bottum_cord;
    double figure_width;
    double figure_height;
} figure_configuration_t;

figure_configuration_t init_figure_configuration(double min_left_cord, double min_bottum_cord,
                                                 double figure_width, double figure_height)
{
    figure_configuration_t config;

    config.min_bottum_cord = min_bottum_cord;
    config.min_left_cord = min_left_cord;
    config.figure_height = figure_height;
    config.figure_width = figure_width;

    return config;
}

static err_t get_figure_projection_width_height_params(figure_configuration_t *config, figure_t *figure)
{
    if (config == NULL || check_wether_figure_is_free(figure) ||figure->point_array_lenght <= 0)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    max_figure_params_t params = init_max_figure_params();

    err_t return_code = get_figure_max_params(&params, figure);

    if (return_code == SUCCESS)
    {
        double real_width = fabs(params.max_right - params.max_left) + 1;
        double real_height = fabs(params.max_top - params.max_bottom) + 1;

        if (return_code == SUCCESS)
        {
            *config = init_figure_configuration(params.max_bottom, params.max_left, real_width, real_height);
        }
    }

    return return_code;
}

err_t set_figure_points_into_window_center(figure_t *figure, object_size_params_t *size_params)
{
    if (figure == NULL || figure->points_array == NULL || size_params == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    figure_configuration_t figure_params;

    err_t return_code = get_figure_projection_width_height_params(&figure_params, figure);

    if (return_code == SUCCESS)
    {
        double k = 0, xm = 0, ym = 0;

        k = fmin(size_params->object_height / figure_params.figure_height / 2,
                 size_params->object_width / figure_params.figure_width / 2);
        xm = - k * figure_params.min_left_cord + k * figure_params.figure_width;
        ym = - k * figure_params.min_bottum_cord + k * figure_params.figure_height;

        scale_coefficients_t scale_coefficiens = init_scale_coefficients(k, -k, k);
        move_coefficients_t move_coefficients = init_move_coefficients(xm, ym, 0.0);

        return_code = scale_figure(figure, &scale_coefficiens);

        if (return_code == SUCCESS)
        {
           return_code = move_figure(figure, &move_coefficients);
        }
    }

    return return_code;
}

err_t read_figure_info_from_file(figure_t *figure, FILE *file)
{
    if (figure == NULL || file == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = read_information_about_points_from_file(&(figure->points_array),
                                                                &(figure->point_array_lenght),
                                                                file);

    if (return_code == SUCCESS)
    {
        return_code = read_information_about_edges_from_file(&(figure->edges_array),
                                                             &(figure->edges_array_length),
                                                             file);
        if (return_code != SUCCESS)
        {
            free(figure->points_array);
        }
    }

    return return_code;
}
