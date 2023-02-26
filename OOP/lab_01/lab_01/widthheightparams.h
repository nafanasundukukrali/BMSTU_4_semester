#ifndef WIDTHHEIGHTPARAMS_H
#define WIDTHHEIGHTPARAMS_H

#include <cstdlib>

typedef struct
{
    double window_height;
    double window_width;
} width_height_params_t;

width_height_params_t init_width_height_params(const double width, const double height);

#endif // WIDTHHEIGHTPARAMS_H
