#include "viewcoefficients.h"

view_coefficients_t init_view_coefficients(const double k, const double xm, const double ym)
{
    view_coefficients_t coefficients;

    coefficients.k = k;
    coefficients.xm = xm;
    coefficients.ym = ym;

    return coefficients;
}

err_t get_view_coefficients_k(view_coefficients_t *coefficients, double *dst_value)
{
    if (coefficients == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = coefficients->k;

    return SUCCESS;
}

err_t get_view_coefficients_xm(view_coefficients_t *coefficients, double *dst_value)
{
    if (coefficients == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = coefficients->xm;

    return SUCCESS;
}

err_t get_view_coefficients_ym(view_coefficients_t *coefficients, double *dst_value)
{
    if (coefficients == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = coefficients->ym;

    return SUCCESS;
}
