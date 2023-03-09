#ifndef VIEWCOEFFICIENTS_H
#define VIEWCOEFFICIENTS_H

#include "error.h"

typedef struct
{
    double k;
    double xm;
    double ym;
} view_coefficients_t;

view_coefficients_t init_view_coefficients(const double k, const double xm, const double ym);
err_t get_view_coefficients_k(view_coefficients_t *coefficients, double *dst_value);
err_t get_view_coefficients_xm(view_coefficients_t *coefficients, double *dst_value);
err_t get_view_coefficients_ym(view_coefficients_t *coefficients, double *dst_value);

#endif // VIEWCOEFFICIENTS_H
