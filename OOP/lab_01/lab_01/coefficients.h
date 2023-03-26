#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

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

typedef struct
{
    void *coefficients;
    double *first_value;
    double *second_value;
    double *third_value;
} get_coefficients_function_params_t;

scale_coefficients_t init_scale_coefficients(const double kx, const double ky, const double kz);
move_coefficients_t init_move_coefficients(const double dx, const double dy, const double dz);
rotate_coefficients_t init_rotate_coefficients(const double angle_x, const double angle_y, const double angle_z);

#endif // COEFFICIENTS_H
