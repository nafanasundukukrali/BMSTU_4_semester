#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsScene>
#include "objectsizeparams.h"
#include "error.h"
#include "figure.h"
#include "graphicscene.h"
#include "viewcoefficients.h"

typedef struct
{
    QGraphicsScene *scene;
    view_coefficients_t coefficient;
    QPen pen;
} graphic_view_t;

graphic_view_t init_graphic_view(QGraphicsScene *scene, QPen pen);
err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_scene, figure_t *figure);

#endif // GRAPHICVIEW_H
