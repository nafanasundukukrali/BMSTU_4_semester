#include "graphicviewstruct.h"

graphic_view_t init_graphic_view(QGraphicsScene *scene, QPen pen)
{
    graphic_view_t graphic_view;

    graphic_view.scene = scene;
    graphic_view.pen = pen;

    return graphic_view;
}

err_t add_line_to_scene(QGraphicsScene *scene, QLineF line, QPen pen)
{
    if (scene == NULL)
        return ERROR_UNCORRECT_PARAMS;

    scene->addLine(line, pen);

    return SUCCESS;
}
