#include "widthheightparams.h"

width_height_params_t init_width_height_params(const double width, const double height)
{
    width_height_params_t params;

    params.window_height = height;
    params.window_width = width;

    return params;
}
