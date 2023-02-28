#include "handler.h"

err_t handler_action(request_t request, void *params)
{
    if (params == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    switch (request)
    {
        case READ:
            return_code = read_action(params);
            break;
        case MOVE:
            return_code = move_action(params);
            break;
        case ROTATE:
            return_code = rotate_action(params);
            break;
        case SCALE:
            return_code = scale_action(params);
            break;
        default:
            return_code = ERROR_UNCORRECT_PARAMS;
    }

    return return_code;
}
