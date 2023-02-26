#ifndef FIGURE_H
#define FIGURE_H

#include <cstdint>

#include "point.h"
#include "edge.h"
#include "widthheightparams.h"

typedef struct
{
    point_t *points_array;
    edge_t *edges_array;
    size_t point_array_lenght;
    size_t edges_array_length;
} figure_t;

typedef struct
{
    err_t *return_code;
    size_t one_object_mem_size;
    size_t count;
} params_alocate_function_t;

typedef struct
{
    double min_left_cord;
    double min_bottum_cord;
    width_height_params_t object_params;
} figure_configuration_t;

figure_t init_figure();
void* allocate_memory_of_object_array(params_alocate_function_t params);
bool check_wether_figure_is_free(figure_t *figure);
err_t free_figure_memory(figure_t *figure);
err_t check_figure_data_correctness(figure_t *figure);
figure_configuration_t get_figure_projection_width_height_params(figure_t figure);

err_t scale_figure(figure_t *figure, scale_coefficients_t *coefficients);
err_t move_figure(figure_t *figure, move_coefficients_t *coefficients);
err_t rotate_figure(figure_t *figure, rotate_coefficients_t *coefficients);

#endif // FIGURE_H
