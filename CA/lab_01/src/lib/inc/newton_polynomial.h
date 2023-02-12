#ifndef __NEWTON_POLYNOMIAL_H__
#define __NEWTON_POLYNOMIAL_H__

#include "input_data.h"
#include "errors.h"
#include "string.h"

int calc_newton_approximation_coefficients(user_data_t*, polynomial_t *);
double get_function_value_newton(user_data_t *, polynomial_t *);

#endif
