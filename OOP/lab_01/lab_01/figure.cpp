#include "figure.h"

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
        return ERROR_UNCORRECT_PARAMS;

    *dst_point = &(figure->points_array[index]);

    return SUCCESS;
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

err_t check_figure_data_uncorrectness(figure_t *figure)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    for (size_t i = 0; i < figure->edges_array_length && return_code == SUCCESS; i++)
    {
        size_t start, end;

        return_code = get_edge_start(&(figure->edges_array[i]), &start);

        if (return_code == SUCCESS)
            return_code = get_edge_end(&(figure->edges_array[i]), &end);


        if (return_code == SUCCESS &&
                (start >= figure->point_array_lenght ||
                end >= figure->point_array_lenght))
            return_code = ERROR_INCORRECT_EDGE_INFO;
    }

    return return_code;
}

err_t get_figure_projection_width_height_params(figure_configuration_t *config, figure_t *figure)
{
    if (config == NULL || figure == NULL || check_figure_data_uncorrectness(figure) ||figure->point_array_lenght <= 0)
        return ERROR_UNCORRECT_PARAMS;

    double max_right = 0, max_left = 0, max_bottom = 0, max_top = 0, buffer_x, buffer_y;

    err_t return_code = SUCCESS;

    return_code = get_x_of_point(&(figure->points_array[0]), &buffer_x);

    if (return_code == SUCCESS)
        return_code = get_y_of_point(&(figure->points_array[0]), &buffer_y);

    if (return_code == SUCCESS)
    {
        max_right = buffer_x;
        max_left = 0;
        max_bottom = 0;
        max_top = buffer_y;
    }

    for (size_t i = 1; return_code == SUCCESS && i < figure->point_array_lenght; i++)
    {
        return_code = get_x_of_point(&(figure->points_array[0]), &buffer_x);

        if (return_code == SUCCESS)
            return_code = get_y_of_point(&(figure->points_array[0]), &buffer_y);

        if (return_code == SUCCESS)
        {
            max_right = fmax(buffer_x, max_right);
            max_left = fmin(buffer_x, max_left);
            max_bottom = fmin(buffer_y, max_bottom);
            max_top = fmax(buffer_y, max_top);
        }
    }

    if (return_code == SUCCESS)
    {
        double real_width = fabs(max_right - max_left) + 1;
        double real_height = fabs(max_top - max_bottom) + 1;

        object_size_params_t params;

        init_object_size_params(&params, real_width, real_height);
        *config = init_figure_configuration(&params, max_left, max_bottom);
    }

    return return_code;
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
        return_code = rotate_point_coords(&(figure->points_array[i]), coefficients);

    return return_code;
}

err_t get_figure_edges_count(figure_t *figure, size_t *dst_value)
{
    if (figure == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = figure->edges_array_length;

    return SUCCESS;
}

err_t get_figure_edge_by_index(figure_t *figure, edge_t **edge, const size_t index)
{
    if (figure == NULL || edge == NULL || *edge == NULL || index > figure->edges_array_length)
        return ERROR_UNCORRECT_PARAMS;

    *edge = &(figure->edges_array[index]);

    return SUCCESS;
}

err_t get_figure_point_by_index(figure_t *figure, point_t **point, const size_t index)
{
    if (figure == NULL || point == NULL || *point == NULL || index > figure->point_array_lenght)
        return ERROR_UNCORRECT_PARAMS;

    *point = &(figure->points_array[index]);

    return SUCCESS;
}

err_t set_figure_points_count(figure_t *figure, const size_t src_value)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure->point_array_lenght = src_value;

    return SUCCESS;
}

err_t set_figure_edges_count(figure_t *figure, const size_t src_value)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure->edges_array_length = src_value;

    return SUCCESS;
}

err_t set_figure_points_array(figure_t *figure, point_t *src_value)
{
    if (figure == NULL || figure->points_array != NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure->points_array = src_value;

    return SUCCESS;
}

err_t set_figure_edges_array(figure_t *figure, edge_t *src_value)
{
    if (figure == NULL || figure->edges_array != NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure->edges_array = src_value;

    return SUCCESS;
}

err_t set_figure_points_into_another_size_params(figure_t *figure, object_size_params_t *size_params)
{
    if (figure == NULL || figure->points_array == NULL || size_params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double global_object_height, global_object_width;

    err_t return_code = get_object_size_height(size_params, &global_object_height);

    if (return_code == SUCCESS)
        return_code = get_object_size_width(size_params, &global_object_width);

    figure_configuration_t figure_params;

    if (return_code == SUCCESS)
        return_code = get_figure_projection_width_height_params(&figure_params, figure);

    double kx = 0, ky = 0, figure_height, figure_width, figure_min_bottum_cord, figure_min_left_cord, k = 0, xm = 0, ym = 0;

    if (return_code == SUCCESS)
        return_code = get_figure_height(&figure_params, &figure_height);

    if (return_code == SUCCESS)
        return_code = get_figure_width(&figure_params, &figure_width);

    if (return_code == SUCCESS)
        return_code = get_figure_min_bottum_cord(&figure_params, &figure_min_bottum_cord);

    if (return_code == SUCCESS)
        return_code = get_figure_min_left_cord(&figure_params, &figure_min_left_cord);

    if (return_code == SUCCESS)
    {
        ky = global_object_height / figure_height / 2;
        kx = global_object_width / figure_width / 2;
        k = fmin(kx, ky);
        xm = - k * figure_min_left_cord + k / k * global_object_width / 2;
        ym = - k * figure_min_bottum_cord + k / k * global_object_height / 2;

        scale_coefficients_t scale_coefficiens = init_scale_coefficients(k, -k, k);
        move_coefficients_t move_coefficients = init_move_coefficients(xm, ym, 0.0);

        return_code = scale_figure(figure, &scale_coefficiens);

        if (return_code == SUCCESS)
           return_code = move_figure(figure, &move_coefficients);
    }

    return return_code;
}
