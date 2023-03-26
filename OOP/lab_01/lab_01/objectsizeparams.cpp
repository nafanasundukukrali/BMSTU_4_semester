#include "objectsizeparams.h"

static bool check_size_correctness(const double size_param)
{
    return size_param >= 0;
}

err_t init_object_size_params(object_size_params_t *params, const double width, const double height)
{
    if (params == NULL || !check_size_correctness(width) || !check_size_correctness(height))
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    params->object_height = height;
    params->object_width = width;

    return SUCCESS;
}

err_t get_object_size_width(double *dst_value, object_size_params_t *width_height_params)
{
    if (width_height_params == NULL || dst_value == NULL ||
            width_height_params->object_height <= 0 || width_height_params->object_width <= 0)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *dst_value = width_height_params->object_width;

    return SUCCESS;
}

err_t get_object_size_width_and_height(double *width, double *height, object_size_params_t *width_height_params)
{
    if (width_height_params == NULL || width == NULL || height == NULL ||
            width_height_params->object_height <= 0 || width_height_params->object_width <= 0)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *width = width_height_params->object_width;
    *height = width_height_params->object_height;

    return SUCCESS;
}

err_t get_object_size_height(double *dst_value, object_size_params_t *width_height_params)
{
    if (width_height_params == NULL || dst_value == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    *dst_value = width_height_params->object_height;

    return SUCCESS;
}

err_t set_object_size_width(object_size_params_t *width_height_params, const double src_value)
{
    if (width_height_params == NULL || !check_size_correctness(src_value))
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    width_height_params->object_width = src_value;

    return SUCCESS;
}

err_t set_object_size_height(object_size_params_t *width_height_params, const double src_value)
{
    if (width_height_params == NULL || !check_size_correctness(src_value))
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    width_height_params->object_height = src_value;

    return SUCCESS;
}
