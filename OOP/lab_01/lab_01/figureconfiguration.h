#ifndef FIGURECONFIGURATION_H
#define FIGURECONFIGURATION_H

#include "objectsizeparams.h"


typedef struct
{
    double min_left_cord;
    double min_bottum_cord;
    double figure_width;
    double figure_height;
} figure_configuration_t;


figure_configuration_t init_figure_configuration(object_size_params_t *params,
                                                        double min_left, double max_bottom);


#endif // FIGURECONFIGURATION_H
