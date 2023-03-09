#ifndef ADDLINE_TO_GRPHIC_SCENE_H
#define ADDLINE_TO_GRPHIC_SCENE_H

#include <QGraphicsScene>
#include "error.h"
#include "point.h"
#include "objectsizeparams.h"

typedef struct
{
    QGraphicsScene *scene;
    point_t *start;
    point_t *end;
    QPen pen;
} add_line_to_graphic_scene_params;

err_t add_line_to_graphic_scene(add_line_to_graphic_scene_params);
err_t clean_graphic_scene(QGraphicsScene *scene);

#endif // ADDLINE_TO_GRPHIC_SCENE_H
