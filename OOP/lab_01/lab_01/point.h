#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include "error.h"
#include "coefficients.h"

#define READING_COORDS_SUCCESS_COUNT 3

typedef struct {
    double x;
    double y;
    double z;
} point_t;

point_t init_point();
bool point_comparator(point_t *a, point_t *b);
err_t scale_point_coords(point_t *dest_point, point_t *src_point, scale_coefficients_t* scale_coefficients);
err_t move_point_coords(point_t *dest_point, point_t *src_point, move_coefficients_t* move_coefficients);
err_t turn_point_coords(point_t *point, rotate_coefficients_t *coefficients);

#endif // POINT_H
