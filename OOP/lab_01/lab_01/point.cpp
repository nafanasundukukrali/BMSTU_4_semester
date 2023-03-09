#include "point.h"
#include <cmath>

point_t init_point(const double x, const double y, const double z)
{
    point_t point;

    point.x = x;
    point.y = y;
    point.z = z;

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

    double kx = 1, ky = 1, kz = 1;

    err_t return_code = get_scale_coefficients({
                                                   scale_coefficients,
                                                   &kx,
                                                   &ky,
                                                   &kz
                                               });

    if (return_code == SUCCESS)
    {
        dest_point->x = src_point->x * kx;
        dest_point->y = src_point->y * ky;
        dest_point->z = src_point->z * kz;
    }

    return return_code;
}

err_t move_point_coords(point_t *dest_point, point_t *src_point, move_coefficients_t* move_coefficients)
{
    if (dest_point == NULL || src_point == NULL || move_coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double dx = 0, dy = 0, dz = 0;

    err_t return_code = get_move_coefficients({
                                                  move_coefficients,
                                                  &dx,
                                                  &dy,
                                                  &dz
                                              });

    if (return_code == SUCCESS)
    {
        dest_point->x = src_point->x + dx;
        dest_point->y = src_point->y + dy;
        dest_point->z = src_point->z + dz;
    }

    return return_code;
}

double convert_to_radians(double (*angle_function)(double), const double angle)
{
    return (*angle_function)(angle * M_PI / 180);
}

static err_t rotate_x_cord(point_t *point, const double angle)
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

static err_t rotate_y_cord(point_t *point, const double angle)
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

static err_t rotate_z_cord(point_t *point, const double angle)
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

err_t rotate_point_coords(point_t *point, rotate_coefficients_t *coefficients)
{
    if (point == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double angle_x = 0, angle_y = 0, angle_z = 0;

    err_t return_code = get_rotate_coefficients({
                                                    coefficients,
                                                    &angle_x,
                                                    &angle_y,
                                                    &angle_z
                                                });

    if (return_code == SUCCESS)
        return_code = rotate_x_cord(point, angle_x);

    if (return_code == SUCCESS)
        return_code = rotate_y_cord(point, angle_y);

    if (return_code == SUCCESS)
        return_code = rotate_z_cord(point, angle_z);

    return return_code;
}

err_t get_x_of_point(point_t *point, double *dst_value)
{
    if (point == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = point->x;

    return SUCCESS;
}

err_t set_x_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    point->x = src_value;

    return SUCCESS;
}

err_t get_y_of_point(point_t *point, double *dst_value)
{
    if (point == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = point->y;

    return SUCCESS;
}

err_t set_y_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    point->y = src_value;

    return SUCCESS;
}

err_t get_z_of_point(point_t *point, double *dst_value)
{
    if (point == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = point->z;

    return SUCCESS;
}

err_t set_z_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
        return ERROR_UNCORRECT_PARAMS;

    point->z = src_value;

    return SUCCESS;
}
