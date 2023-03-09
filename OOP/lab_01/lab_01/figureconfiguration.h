#ifndef FIGURECONFIGURATION_H
#define FIGURECONFIGURATION_H

#include "objectsizeparams.h"

typedef struct
{
    double min_left_cord;
    double min_bottum_cord;
    object_size_params_t *object_params;
} figure_configuration_t;


figure_configuration_t init_figure_configuration(object_size_params_t *params,
                                                        double min_left, double max_bottom);
err_t get_figure_min_left_cord(figure_configuration_t *config, double *dst_value);
err_t get_figure_min_bottum_cord(figure_configuration_t *config, double *dst_value);
err_t get_figure_width(figure_configuration_t *config, double *dst_value);
err_t get_figure_height(figure_configuration_t *config, double *dst_value);

#endif // FIGURECONFIGURATION_H
