#include "point.h"
#include <cmath>

point_t init_point()
{
    point_t point;

    point.x = 0;
    point.y = 0;
    point.z = 0;

    return point;
}

bool point_comparator(point_t *a, point_t *b)
{
    return a != NULL && b != NULL && a->x == b->x && a->y == b->y;
}

err_t scale_point_coords(point_t *dest_point, point_t *src_point, scale_coefficients_t* scale_coefficients)
{
    if (dest_point == NULL || src_point == NULL || scale_coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    dest_point->x = src_point->x * scale_coefficients->kx;
    dest_point->y = src_point->y * scale_coefficients->ky;
    dest_point->z = src_point->z * scale_coefficients->kz;

    return SUCCESS;
}

err_t move_point_coords(point_t *dest_point, point_t *src_point, move_coefficients_t* move_coefficients)
{
    if (dest_point == NULL || src_point == NULL || move_coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    dest_point->x = src_point->x + move_coefficients->dx;
    dest_point->y = src_point->y + move_coefficients->dy;
    dest_point->z = src_point->z + move_coefficients->dz;

    return SUCCESS;
}

double convert_to_radians(double (*angle_function)(double), const double angle)
{
    return (*angle_function)(angle * M_PI / 180);
}

static err_t turn_x_cord(point_t *point, const double angle)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double cos_radians = convert_to_radians(cos, angle);
    double sin_radians = convert_to_radians(sin, angle);
    double buffer_y = point->y;

    point->y = point->y + cos_radians + point->z * sin_radians;
    point->z = point->z * cos_radians - buffer_y * sin_radians;

    return SUCCESS;
}

static err_t turn_y_cord(point_t *point, const double angle)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double cos_radians = convert_to_radians(cos, angle);
    double sin_radians = convert_to_radians(sin, angle);
    double buffer_x = point->x;

    point->x = point->x * cos_radians + point->z * sin_radians;
    point->z = point->z * cos_radians - buffer_x * sin_radians;

    return SUCCESS;
}

static err_t turn_z_cord(point_t *point, const double angle)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double cos_radians = convert_to_radians(cos, angle);
    double sin_radians = convert_to_radians(sin, angle);
    double buffer_x = point->x;

    point->x = point->x * cos_radians + point->y * sin_radians;
    point->y = point->y * cos_radians - buffer_x * sin_radians;

    return SUCCESS;
}

err_t turn_point_coords(point_t *point, rotate_coefficients_t *coefficients)
{
    if (point == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = turn_x_cord(point, coefficients->angle_x);

    if (return_code == SUCCESS)
        return_code = turn_y_cord(point, coefficients->angle_y);

    if (return_code == SUCCESS)
        return_code = turn_z_cord(point, coefficients->angle_z);

    return return_code;
}

