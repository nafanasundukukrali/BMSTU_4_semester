#include "objectsizeparams.h"


object_size_params_t global_window_size_params = {UNINITIALIZED_SIZE,
                                                 UNINITIALIZED_SIZE};

static bool check_size_correctness(const double size_param)
{
    return size_param >= 0;
}

err_t set_global_window_size_params(const double width, const double height)
{
    if (!check_size_correctness(width) || !check_size_correctness(height))
        return ERROR_UNCORRECT_PARAMS;

    global_window_size_params.object_width = width;
    global_window_size_params.object_height = height;

    return SUCCESS;
}

err_t get_global_window_size_params_width(double *dst_value_height,
                                          double *dst_value_width)
{
    if (global_window_size_params.object_height == UNINITIALIZED_SIZE ||
            global_window_size_params.object_width == UNINITIALIZED_SIZE)
        return ERROR_GLOBAL_WINDOW_PARAMS_NOT_SET;

    if (dst_value_height == NULL | dst_value_width == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value_width = global_window_size_params.object_width;
    *dst_value_height = global_window_size_params.object_height;

    return SUCCESS;
}

err_t init_object_size_params(object_size_params_t *params, const double width, const double height)
{
    if (params == NULL || !check_size_correctness(width) || !check_size_correctness(height))
        return ERROR_UNCORRECT_PARAMS;

    params->object_height = height;
    params->object_width = width;

    return SUCCESS;
}

err_t get_object_size_width(object_size_params_t *width_height_params, double *dst_value)
{
    if (width_height_params == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = width_height_params->object_width;

    return SUCCESS;
}

err_t get_object_size_height(object_size_params_t *width_height_params, double *dst_value)
{
    if (width_height_params == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = width_height_params->object_height;

    return SUCCESS;
}

err_t set_object_size_width(object_size_params_t *width_height_params, const double src_value)
{
    if (width_height_params == NULL || !check_size_correctness(src_value))
        return ERROR_UNCORRECT_PARAMS;

    width_height_params->object_width = src_value;

    return SUCCESS;
}

err_t set_object_size_height(object_size_params_t *width_height_params, const double src_value)
{
    if (width_height_params == NULL || !check_size_correctness(src_value))
        return ERROR_UNCORRECT_PARAMS;

    width_height_params->object_height = src_value;

    return SUCCESS;
}
