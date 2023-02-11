#ifndef __HERMITE_POLYNOMIAL_H__
#define __HERMITE_POLYNOMIAL_H__

#include "input_data.h"
#include "errors.h"
#include "string.h"

typedef struct
{
    double *coefficients;
    double *x;
} hermite_polynomial_t;

// int calc_newton_approximation_coefficients(user_data_t*, newton_polynomial_t *);
// double get_function_value_newton(user_data_t *, newton_polynomial_t *);

#endif
