#ifndef ADDLINE_TO_GRPHIC_SCENE_H
#define ADDLINE_TO_GRPHIC_SCENE_H

#include "error.h"
#include "point.h"
#include "graphicviewstruct.h"

typedef struct
{
    graphic_view_t *graphic_view;
    point_t *start;
    point_t *end;
} add_line_to_graphic_scene_params;

err_t add_line_to_graphic_view(graphic_view_t *graphic_view_params,
                                                    point_t *start,
                                                    point_t *end);
err_t clean_graphic_scene(QGraphicsScene *scene);


#endif // ADDLINE_TO_GRPHIC_SCENE_H
