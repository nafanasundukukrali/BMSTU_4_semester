#include "handler.h"

err_t handler_action(request_type_t request, action_params_t *params)
{
    figure_t figure;

    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    switch (request)
    {
        case READ:
            return_code = read_action(figure, *params);
            break;
        case MOVE:
            return_code = move_action(figure, *params);
            break;
        case ROTATE:
            return_code = rotate_action(figure, *params);
            break;
        case SCALE:
            return_code = scale_action(figure, *params);
            break;
        case PREPARE_FOR_DRAW:
            return_code = prepare_figure_for_draw_action(figure, *params);
            break;
        default:
            return_code = ERROR_UNCORRECT_PARAMS;
    }

    return return_code;
}
