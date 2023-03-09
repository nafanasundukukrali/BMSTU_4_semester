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

err_t prepare_figure(figure_t *figure, move_coefficients_t *move_coefficients, scale_coefficients_t *scale_coefficients)
{
    if (figure == NULL || figure->points_array == NULL || move_coefficients == NULL || scale_coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = move_figure(figure, move_coefficients);

    if (return_code == SUCCESS)
        return_code = scale_figure(figure, scale_coefficients);

    return return_code;
}

err_t copy_figure_with_memory(figure_t *src_figure, figure_t *dst_figure)
{
    if (src_figure == NULL || check_figure_data_uncorrectness(src_figure) ||
            dst_figure == NULL || !check_wether_figure_is_free(dst_figure))
        return ERROR_NO_LOADED_FIGURE;

    err_t return_code = SUCCESS;
    figure_t buffer;

    buffer.points_array = (point_t *)allocate_memory_of_object_array({
                                                                   &return_code,
                                                                   sizeof(point_t),
                                                                   src_figure->point_array_lenght,
                                                               });

    if (return_code == SUCCESS)
        buffer.edges_array = (edge_t *)allocate_memory_of_object_array({
                                                                       &return_code,
                                                                       sizeof(edge_t),
                                                                       src_figure->edges_array_length,
                                                                   });

    if (return_code == SUCCESS)
        memmove(buffer.points_array, src_figure->points_array, sizeof(point_t) * src_figure->point_array_lenght);

    if (return_code == SUCCESS && buffer.points_array == NULL)
        return_code = ERROR_COPY_FIGURE;

    if (return_code == SUCCESS)
        memmove(buffer.edges_array, src_figure->edges_array, sizeof(edge_t) * src_figure->edges_array_length);

    if (return_code == SUCCESS && buffer.edges_array == NULL)
        return_code = ERROR_COPY_FIGURE;

    if (return_code != SUCCESS)
    {
        free_figure_memory(&buffer);
    }
    else
    {
        *dst_figure = buffer;
        dst_figure->point_array_lenght = src_figure->point_array_lenght;
        dst_figure->edges_array_length = src_figure->edges_array_length;
    }

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
