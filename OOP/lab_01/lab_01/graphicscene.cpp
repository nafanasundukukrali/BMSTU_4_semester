#include "graphicscene.h"

err_t add_line_to_graphic_view(graphic_view_t *graphic_view, point_t *start, point_t *end)
{
    if (graphic_view == NULL || start == NULL || end == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    double buffer_start_x = 0, buffer_start_y = 0;
    double buffer_end_x = 0, buffer_end_y = 0;

    err_t return_code = get_drawing_cords_of_point(&buffer_start_x, &buffer_start_y, start);

    if (return_code == SUCCESS)
    {
        return_code =  get_drawing_cords_of_point(&buffer_end_x, &buffer_end_y, end);

        if (return_code == SUCCESS)
        {
            QLineF line = QLineF(buffer_start_x, buffer_start_y, buffer_end_x, buffer_end_y);

            return_code = add_line_to_scene(graphic_view->scene, line, graphic_view->pen);
        }
    }

    return return_code;
}

err_t clean_graphic_scene(QGraphicsScene *scene)
{
    if (scene == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    scene->clear();

    return SUCCESS;
}
