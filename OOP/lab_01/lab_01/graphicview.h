#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include "objectsizeparams.h"
#include "error.h"
#include "figure.h"
#include "graphicscene.h"
#include "graphicviewstruct.h"

err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_scene, figure_t *figure);

#endif // GRAPHICVIEW_H
