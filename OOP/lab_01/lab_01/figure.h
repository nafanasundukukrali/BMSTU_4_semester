#ifndef FIGURE_H
#define FIGURE_H

#include <cstdint>

#include "point.h"
#include "edge.h"
#include "objectsizeparams.h"

typedef struct
{
    point_t *points_array;
    edge_t *edges_array;
    size_t point_array_lenght;
    size_t edges_array_length;
} figure_t;

figure_t init_figure();
bool check_wether_figure_is_free(figure_t *figure);
err_t free_figure_memory(figure_t *figure);
err_t check_figure_correctness(figure_t *figure);

err_t scale_figure(figure_t *figure, scale_coefficients_t *coefficients);
err_t move_figure(figure_t *figure, move_coefficients_t *coefficients);
err_t rotate_figure(figure_t *figure, rotate_coefficients_t *coefficients);

err_t get_figure_edges_count(size_t *dst_value, figure_t *figure);
err_t get_point_info_by_index(point_t **dst_point, figure_t *figure, const size_t index);
err_t get_figure_edge_by_index(edge_t **edge, figure_t *figure, const size_t index);
err_t get_figure_point_by_index(point_t **point, figure_t *figure, const size_t index);

err_t set_figure_points_information(figure_t *figure, point_t *array_pointer, const size_t array_length);
err_t set_figure_edges_information(figure_t *figure, edge_t *array_pointer, const size_t array_length);

err_t set_figure_points_into_window_center(figure_t *figure, object_size_params_t *size_params);

err_t free_points_data(figure_t *figure);
err_t free_edges_data(figure_t *figure);

err_t read_figure_info_from_file(figure_t *figure, FILE *file);

#endif // FIGURE_H
