#include "coefficients.h"

scale_coefficients_t init_scale_coefficients(double kx, double ky, double kz)
{
    scale_coefficients_t scale_coefficients;

    scale_coefficients.kx = kx;
    scale_coefficients.ky = ky;
    scale_coefficients.kz = kz;

    return scale_coefficients;
}

move_coefficients_t init_move_coefficients(double dx, double dy, double dz)
{
    move_coefficients_t move_coefficients;

    move_coefficients.dx = dx;
    move_coefficients.dy = dy;
    move_coefficients.dz = dz;

    return move_coefficients;
}

rotate_coefficients_t init_rotate_coefficients(double angle_x, double angle_y, double angle_z)
{
    rotate_coefficients_t rotate_coefficients;

    rotate_coefficients.angle_x = angle_x;
    rotate_coefficients.angle_y = angle_y;
    rotate_coefficients.angle_z = angle_z;

    return rotate_coefficients;
}

err_t get_scale_coefficients(get_coefficients_function_params_t params)
{
    if (params.coefficients == NULL || params.first_value == NULL ||
            params.second_value == NULL || params.third_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    scale_coefficients_t *coefficients = (scale_coefficients_t *)params.coefficients;

    *(params.first_value) = coefficients->kx;
    *(params.second_value) = coefficients->ky;
    *(params.third_value) = coefficients->kz;

    return SUCCESS;
}


err_t get_move_coefficients(get_coefficients_function_params_t params)
{
    if (params.coefficients == NULL || params.first_value == NULL ||
            params.second_value == NULL || params.third_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    move_coefficients_t *coefficients = (move_coefficients_t *)params.coefficients;

    *(params.first_value) = coefficients->dx;
    *(params.second_value) = coefficients->dy;
    *(params.third_value) = coefficients->dz;

    return SUCCESS;
}


err_t get_rotate_coefficients(get_coefficients_function_params_t params)
{
    if (params.coefficients == NULL || params.first_value == NULL ||
            params.second_value == NULL || params.third_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    rotate_coefficients_t *coefficients = (rotate_coefficients_t *)params.coefficients;

    *(params.first_value) = coefficients->angle_x;
    *(params.second_value) = coefficients->angle_y;
    *(params.third_value) = coefficients->angle_z;

    return SUCCESS;
}
