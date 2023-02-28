#include "request.h"
#include "fileio.h"

read_action_coefficients_t init_read_action_coefficients(QString *file_path, figure_t *figure, graphic_view_t *scene)
{
    read_action_coefficients_t read_coefficients;

    read_coefficients.figure = figure;
    read_coefficients.file_path = file_path;
    read_coefficients.graphicScene = scene;

    return read_coefficients;
}

scale_action_coefficients_t init_scale_action_coefficients(figure_t *figure, scale_coefficients_t *coefficients)
{
    scale_action_coefficients_t scale_coefficients;

    scale_coefficients.coefficients =  coefficients;
    scale_coefficients.figure = figure;

    return scale_coefficients;
}

move_action_coefficients_t init_move_action_coefficients(figure_t *figure, move_coefficients_t *coefficients)
{
    move_action_coefficients_t move_coefficients;

    move_coefficients.coefficients =  coefficients;
    move_coefficients.figure = figure;

    return move_coefficients;
}

rotate_action_coefficients_t init_rotate_action_coefficients(figure_t *figure, rotate_coefficients_t *coefficients)
{
    rotate_action_coefficients_t rotate_coefficients;

    rotate_coefficients.coefficients = coefficients;
    rotate_coefficients.figure = figure;

    return rotate_coefficients;
}

err_t read_action(void *params)
{
    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    read_action_coefficients_t *buffer_params = (read_action_coefficients_t *)params;

    FILE *file;
    char *file_path_char_string = buffer_params->file_path->toLocal8Bit().data();

    figure_t buffer_figure = init_figure();

    err_t return_code = open_file_by_path(file_path_char_string, &file);

    if (return_code == SUCCESS)
       return_code = read_data_from_file(file, &buffer_figure);

    if (fclose(file))
       return_code = ERROR_CLOSE_FILE;

    if (return_code == SUCCESS)
        return_code = check_figure_data_correctness(&buffer_figure);

    if (return_code == SUCCESS)
    {
       if (!check_wether_figure_is_free(buffer_params->figure))
           free_figure_memory(buffer_params->figure);

       *(buffer_params->figure) = buffer_figure;
    }

    return return_code;
}

err_t scale_action(void *params)
{
    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    scale_action_coefficients_t *tmp_params = (scale_action_coefficients_t *)params;

    return scale_figure(tmp_params->figure, tmp_params->coefficients);
}

err_t move_action(void *params)
{
    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    move_action_coefficients_t *tmp_params = (move_action_coefficients_t *)params;

    return move_figure(tmp_params->figure, tmp_params->coefficients);
}

err_t rotate_action(void *params)
{
    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    rotate_action_coefficients_t *tmp_params = (rotate_action_coefficients_t *)params;

    return rotate_figure(tmp_params->figure, tmp_params->coefficients);
}
