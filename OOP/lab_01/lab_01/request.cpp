#include "request.h"
#include "fileio.h"

action_params_t init_action_params(action_params_t params)
{
    action_params_t action_params;

    action_params = params;

    return action_params;
}

err_t read_action(figure_t *figure, action_params_t *params)
{
    if (params == NULL || params->path == NULL || params->window_params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure_t buffer_figure = init_figure();

    err_t return_code = read_data_from_file(&buffer_figure, params->path);

    if (return_code == SUCCESS)
        return_code = check_figure_data_uncorrectness(&buffer_figure);

    if (return_code == SUCCESS)
        return_code = set_figure_points_into_another_size_params(&buffer_figure, params->window_params);

    if (return_code == SUCCESS)
    {
       if (!check_wether_figure_is_free(figure))
           free_figure_memory(figure);

       *(figure) = buffer_figure;
    }

    if (return_code != SUCCESS && !check_wether_figure_is_free(&buffer_figure))
        free_figure_memory(&buffer_figure);

    return return_code;
}

err_t scale_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->scale_coefficients == NULL ||
            check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return scale_figure(figure, params->scale_coefficients);
}

err_t move_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->move_coefficients == NULL ||
            check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return move_figure(figure, params->move_coefficients);
}

err_t rotate_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->rotate_coefficients == NULL ||
            check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return rotate_figure(figure, params->rotate_coefficients);
}

err_t draw_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || check_wether_figure_is_free(figure) || params == NULL || params->grapgic_view == NULL)
        return ERROR_UNCORRECT_PARAMS;

    return draw_figure_orthogonal_projection(params->grapgic_view, figure);
}

err_t free_action(figure_t *figure)
{
    if (figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    free_figure_memory(figure);

    return SUCCESS;
}

