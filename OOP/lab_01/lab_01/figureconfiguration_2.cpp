#include "figureconfiguration.h"

figure_configuration_t init_figure_configuration(object_size_params_t *params,
                                                        double min_left, double max_bottom)
{
    figure_configuration_t config;

    config.object_params = *params;
    config.min_bottum_cord = max_bottom;
    config.min_left_cord = min_left;

    return config;
}

err_t get_figure_min_left_cord(double *dst_value, figure_configuration_t *config)
{
    if (config == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = config->min_left_cord;

    return SUCCESS;
}

err_t get_figure_min_bottum_cord(double *dst_value, figure_configuration_t *config)
{
    if (config == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    *dst_value = config->min_bottum_cord;

    return SUCCESS;
}

err_t get_figure_width(double *dst_value, figure_configuration_t *config)
{
    if (config == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double buffer;

    err_t return_code = get_object_size_width(&buffer, &(config->object_params));

    if (return_code == SUCCESS)
        *dst_value = buffer;

    return SUCCESS;
}

err_t get_figure_height(double *dst_value, figure_configuration_t *config)
{
    if (config == NULL || dst_value == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double buffer;

    err_t return_code = get_object_size_height(&buffer, &(config->object_params));

    if (return_code == SUCCESS)
        *dst_value = buffer;

    return SUCCESS;
}

err_t get_figure_width_and_height(double *width, double *height, figure_configuration_t *config)
{

    if (config == NULL || width == NULL || height == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double buffer;

    err_t return_code = get_object_size_height(&buffer, &(config->object_params));

    if (return_code == SUCCESS)
    {
        *height = buffer;

        return_code = get_object_size_width(&buffer, &(config->object_params));

        if (return_code == SUCCESS)
            *width = buffer;
    }

    return SUCCESS;
}
