#ifndef WIDTHHEIGHTPARAMS_H
#define WIDTHHEIGHTPARAMS_H

#include <cstdlib>
#include "error.h"

#define UNINITIALIZED_SIZE 0

typedef struct
{
    double object_height;
    double object_width;
} object_size_params_t;

err_t init_object_size_params(object_size_params_t *params, const double width, const double height);

err_t get_object_size_width(double *dst_value, object_size_params_t *width_height_params);
err_t get_object_size_height(double *dst_value, object_size_params_t *width_height_params);
err_t set_object_size_width(object_size_params_t *width_height_params, const double src_value);
err_t set_object_size_height(object_size_params_t *width_height_params, const double src_value);
err_t get_object_size_width_and_height(double *width, double *height, object_size_params_t *width_height_params);

#endif // WIDTHHEIGHTPARAMS_H
