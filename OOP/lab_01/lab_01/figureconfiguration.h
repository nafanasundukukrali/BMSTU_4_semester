#ifndef FIGURECONFIGURATION_H
#define FIGURECONFIGURATION_H

#include "objectsizeparams.h"

typedef struct
{
    double min_left_cord;
    double min_bottum_cord;
    object_size_params_t object_params;
} figure_configuration_t;


figure_configuration_t init_figure_configuration(object_size_params_t *params,
                                                        double min_left, double max_bottom);
err_t get_figure_min_left_cord(double *dst_value, figure_configuration_t *config);
err_t get_figure_min_bottum_cord(double *dst_value, figure_configuration_t *config);
err_t get_figure_width(double *dst_value, figure_configuration_t *config);
err_t get_figure_height(double *dst_value, figure_configuration_t *config);

#endif // FIGURECONFIGURATION_H
