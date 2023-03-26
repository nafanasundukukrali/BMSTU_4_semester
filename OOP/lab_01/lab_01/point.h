#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include "error.h"
#include "coefficients.h"
#include "filebasemanipulations.h"

#define READING_COORDS_SUCCESS_COUNT 3

typedef struct {
    double x;
    double y;
    double z;
} point_t;

point_t init_point(const double x, const double y, const double z);
bool point_comparator(point_t *a, point_t *b);

err_t scale_point_coords(point_t *point, scale_coefficients_t *coefficients);
err_t move_point_coords(point_t *point, move_coefficients_t *coefficients);
err_t rotate_point_coords(point_t *point, rotate_coefficients_t *coefficients);

err_t set_x_of_point(point_t *point, const double src_value);
err_t set_y_of_point(point_t *point, const double src_value);

err_t get_z_of_point(double *dst_value, point_t *point);
err_t set_z_of_point(point_t *point, const double src_value);

err_t get_drawing_cords_of_point(double *x, double *y, point_t *point);
err_t read_information_about_points_from_file(point_t **point_array, size_t *point_count, FILE *file);

#endif // POINT_H
