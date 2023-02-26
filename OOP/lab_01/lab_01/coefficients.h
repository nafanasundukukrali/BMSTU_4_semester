#ifndef SCALECOEFFICIENTS_H
#define SCALECOEFFICIENTS_H

typedef struct
{
    double kx;
    double ky;
    double kz;
} scale_coefficients_t;

typedef struct
{
    double dx;
    double dy;
    double dz;
} move_coefficients_t;

typedef struct
{
    double angle_x;
    double angle_y;
    double angle_z;
} rotate_coefficients_t;

scale_coefficients_t init_scale_coefficients(double kx, double ky, double kz);
move_coefficients_t init_move_coefficients(double dx, double dy, double dz);
rotate_coefficients_t init_rotate_coefficients(double angle_x, double angle_y, double angle_z);

#endif // SCALECOEFFICIENTS_H
