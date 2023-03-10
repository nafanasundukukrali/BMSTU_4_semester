#ifndef FIGURE_H
#define FIGURE_H

#include <cstdint>

#include "point.h"
#include "edge.h"
#include "figureconfiguration.h"
#include "memoryallocate.h"

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
err_t check_figure_data_uncorrectness(figure_t *figure);
err_t get_figure_projection_width_height_params(figure_configuration_t *config, figure_t *figure);

err_t scale_figure(figure_t *figure, scale_coefficients_t *coefficients);
err_t move_figure(figure_t *figure, move_coefficients_t *coefficients);
err_t rotate_figure(figure_t *figure, rotate_coefficients_t *coefficients);
err_t prepare_figure(figure_t *figure, move_coefficients_t *move_coefficients, scale_coefficients_t *scale_coefficients);

err_t copy_figure_with_memory(figure_t *src_figure, figure_t *dst_figure);
err_t get_figure_edges_count(figure_t *figure, size_t *dst_value);
err_t get_figure_edge_by_index(figure_t *figure, edge_t **edge, const size_t index);
err_t get_figure_point_by_index(figure_t *figure, point_t **point, const size_t index);

err_t set_figure_points_count(figure_t *figure, const size_t src_value);
err_t set_figure_edges_count(figure_t *figure, const size_t src_value);
err_t set_figure_points_array(figure_t *figure, point_t *src_value);
err_t set_figure_edges_array(figure_t *figure, edge_t *src_value);

#endif // FIGURE_H
