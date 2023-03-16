#include "graphicview.h"
#include "figure.h"

graphic_view_t init_graphic_view(QGraphicsScene *scene, QPen pen)
{
    graphic_view_t graphic_view;

    graphic_view.scene = scene;
    graphic_view.pen = pen;

    return graphic_view;
}

err_t draw_one_edge_of_figure_by_index(graphic_view_t *graphic_view, figure_t *figure, const size_t index)
{
    if (graphic_view == NULL || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    edge_t *edge;
    point_t *start, *end;
    size_t start_index, end_index;

    err_t return_code = get_figure_edge_by_index(&edge, figure, index);

    if (return_code == SUCCESS)
    {
        return_code = get_edge_start(edge, &start_index);

        if (return_code == SUCCESS)
            return_code = get_edge_end(edge, &end_index);

        if (return_code == SUCCESS)
            return_code = get_figure_point_by_index(figure, &start, start_index);

        if (return_code == SUCCESS)
            return_code = get_figure_point_by_index(figure, &end, end_index);
    }

    if (return_code == SUCCESS)
        return_code = add_line_to_graphic_scene({
                                                    graphic_view->scene,
                                                    start,
                                                    end,
                                                    graphic_view->pen
                                                });

    return return_code;
}

err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_view, figure_t *figure)
{
    if (graphic_view == NULL || graphic_view->scene == NULL || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = SUCCESS;

    if (return_code == SUCCESS)
        return_code = clean_graphic_scene(graphic_view->scene);

    size_t edges_count;

    if (return_code == SUCCESS)
        return_code = get_figure_edges_count(&edges_count, figure);

    for (size_t i = 0; return_code == SUCCESS && i < edges_count; i++)
        return_code = draw_one_edge_of_figure_by_index(graphic_view, figure, i);

    return return_code;
}
