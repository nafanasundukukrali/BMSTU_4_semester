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
