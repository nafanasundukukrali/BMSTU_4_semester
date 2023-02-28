#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsScene>
#include "widthheightparams.h"
#include "error.h"
#include "figure.h"

typedef struct
{
    double k;
    double xm;
    double ym;
} view_coefficients_t;

typedef struct
{
    QGraphicsScene *scene;
    width_height_params_t *window_params;
    view_coefficients_t coefficient;
    QPen pen;
} graphic_view_t;

graphic_view_t init_graphic_view(QGraphicsScene *scene, width_height_params_t *params, QPen pen);
err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_scene, figure_t *figure);

#endif // GRAPHICVIEW_H
