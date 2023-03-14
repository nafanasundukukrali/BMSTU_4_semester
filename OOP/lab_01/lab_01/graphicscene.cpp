#include "graphicscene.h"

err_t add_line_to_graphic_scene(add_line_to_graphic_scene_params params)
{
    if (params.scene== NULL || params.start == NULL || params.end == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double buffer_start_x, buffer_start_y;
    double buffer_end_x, buffer_end_y;
    double window_height, window_width;

    err_t return_code = get_x_of_point(params.start, &buffer_start_x);

    if (return_code == SUCCESS)
        return_code = get_y_of_point(params.start, &buffer_start_y);

    if (return_code == SUCCESS)
        return_code = get_x_of_point(params.end, &buffer_end_x);

    if (return_code == SUCCESS)
        return_code = get_y_of_point(params.end, &buffer_end_y);

    if (return_code == SUCCESS)
        params.scene->addLine(buffer_start_x, buffer_start_y, buffer_end_x, buffer_end_y, params.pen);

    return return_code;
}

err_t clean_graphic_scene(QGraphicsScene *scene)
{
    if (scene == NULL)
        return ERROR_UNCORRECT_PARAMS;

    scene->clear();

    return SUCCESS;
}
