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

err_t scale_point_coords(point_t *point, scale_coefficients_t *coefficients)
{
    if (point == NULL || coefficients == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point->x *= coefficients->kx;
    point->y *= coefficients->ky;
    point->z *= coefficients->kz;

    return SUCCESS;
}

err_t move_point_coords(point_t *point, move_coefficients_t *coefficients)
{
    if (coefficients == NULL || point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point->x += coefficients->dx;
    point->y += coefficients->dy;
    point->z += coefficients->dz;

    return SUCCESS;
}

static double convert_to_radians(double (*angle_function)(double), const double angle)
{
    return (*angle_function)(angle * M_PI / 180);
}

static err_t rotate_x_cord(point_t *point, const double angle)
{
    if (point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

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
    {
        return ERROR_UNCORRECT_PARAMS;
    }

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
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    double cos_radians = convert_to_radians(cos, angle);
    double sin_radians = convert_to_radians(sin, angle);
    double buffer_x = point->x;

    point->x = point->x * cos_radians + point->y * sin_radians;
    point->y = point->y * cos_radians - buffer_x * sin_radians;

    return SUCCESS;
}

err_t rotate_point_coords(point_t *point, rotate_coefficients_t *coefficients)
{
    if (coefficients == NULL || point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point_t buffer = *point;

    err_t return_code = rotate_x_cord(&buffer, coefficients->angle_x);

    if (return_code == SUCCESS)
    {
        return_code = rotate_y_cord(&buffer, coefficients->angle_y);

        if (return_code == SUCCESS)
        {
            return_code = rotate_z_cord(&buffer, coefficients->angle_z);

            if (return_code == SUCCESS)
            {
                *point = buffer;
            }
        }
    }

    return return_code;
}

err_t set_x_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point->x = src_value;

    return SUCCESS;
}

err_t set_y_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point->y = src_value;

    return SUCCESS;
}

err_t set_z_of_point(point_t *point, const double src_value)
{
    if (point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    point->z = src_value;

    return SUCCESS;
}

err_t get_drawing_cords_of_point(double *x, double *y, point_t *point)
{
    if (x == NULL || y == NULL || point == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *x = point->x;
    *y = point->y;

    return SUCCESS;
}

static err_t read_point_data_from_file(void *point, FILE *file)
{
    if (point == NULL || file == NULL || feof(file) || ferror(file))
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;
    double x, y, z;

    if (fscanf(file, "%lf%lf%lf", &x, &y, &z) != READING_COORDS_SUCCESS_COUNT)
    {
        return_code = ERROR_READ_DATA;
    }
    else
    {
        point_t *point_pointer = (point_t *)point;
        *point_pointer = init_point(x, y, z);
    }

    return return_code;
}

static err_t malloc_point_array(point_t **array_pointer, const size_t malloc_size)
{
    point_t *buffer = NULL;
    err_t return_code = SUCCESS;

    buffer = (point_t *) malloc(malloc_size * sizeof(point_t));

    if (buffer == NULL)
    {
        return_code = ERROR_ALLOCATE_MEMORY;
    }
    else
    {
        *array_pointer = buffer;
    }

    return return_code;
}

err_t read_array_data_from_file(point_t *array, FILE *file, const size_t array_length)
{
    if (array == NULL || file == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    for (size_t i = 0; i < array_length && return_code == SUCCESS; i += 1)
    {
        return_code = read_point_data_from_file(&(array[i]), file);
    }

    return return_code;
}

err_t read_information_about_points_from_file(point_t **point_array, size_t *point_count, FILE *file)
{
    if (file == NULL ||point_array == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t return_code = SUCCESS;

    return_code = read_size_t_number_from_file(point_count, file);

    if (return_code == SUCCESS)
    {
        return_code = malloc_point_array(point_array, *point_count);

        if (return_code == SUCCESS)
        {
            return_code = read_array_data_from_file(*point_array, file, *point_count);

            if (return_code != SUCCESS)
            {
                free(*point_array);
            }
        }
    }

    return return_code;
}
