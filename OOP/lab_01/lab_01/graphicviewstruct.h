#ifndef GRAPHICVIEWSTRUCT_H
#define GRAPHICVIEWSTRUCT_H

#include <QGraphicsScene>
#include "QLineF"
#include "error.h"

typedef struct
{
    QGraphicsScene *scene;
    QPen pen;
} graphic_view_t;

graphic_view_t init_graphic_view(QGraphicsScene *scene, QPen pen);
err_t add_line_to_scene(QGraphicsScene *scene, QLineF line, QPen pen);

#endif // GRAPHICVIEWSTRUCT_H
