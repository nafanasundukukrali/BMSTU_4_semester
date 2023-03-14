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
    if (figure == NULL || params == NULL || params->path == NULL)
        return ERROR_UNCORRECT_PARAMS;

    FILE *file;
    figure_t buffer_figure = init_figure();

    err_t return_code = open_file_by_path(params->path, &file);

    if (return_code == SUCCESS)
       return_code = read_data_from_file(file, &buffer_figure);

    if (fclose(file))
       return_code = ERROR_CLOSE_FILE;

    if (return_code == SUCCESS)
        return_code = check_figure_data_uncorrectness(&buffer_figure);

    if (return_code == SUCCESS)
    {
       if (!check_wether_figure_is_free(figure))
           free_figure_memory(figure);

       *(figure) = buffer_figure;
    }

    return return_code;
}

err_t scale_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->scale_coefficients == NULL ||
            !check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return scale_figure(figure, params->scale_coefficients);
}

err_t move_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->move_coefficients == NULL ||
            !check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return move_figure(figure, params->move_coefficients);
}

err_t rotate_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params == NULL ||
            params->rotate_coefficients == NULL ||
            !check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return rotate_figure(figure, params->rotate_coefficients);
}

err_t draw_action(figure_t *figure, action_params_t *params)
{
    if (figure == NULL || params.move_coefficients == NULL ||
            params.scale_coefficients == NULL || !check_wether_figure_is_free(figure))
        return ERROR_UNCORRECT_PARAMS;

    return prepare_figure(figure, params.move_coefficients, params.scale_coefficients);
}
