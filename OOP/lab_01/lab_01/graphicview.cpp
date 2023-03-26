#include "graphicview.h"
#include "figure.h"

err_t draw_one_edge_of_figure(graphic_view_t *graphic_view, figure_t *figure, edge_t *edge)
{
    if (graphic_view == NULL || figure == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    size_t start_index = 0, end_index = 0;
    err_t return_code = get_edge_points_indeces(&start_index, &end_index, edge);

    if (return_code == SUCCESS)
    {
        point_t *start = NULL, *end = NULL;
        return_code = get_figure_point_by_index(&start, figure, start_index);

        if (return_code == SUCCESS)
        {
            return_code = get_figure_point_by_index(&end, figure, end_index);

            if (return_code == SUCCESS)
            {
                return_code = add_line_to_graphic_view(graphic_view, start, end);
            }
        }
    }

    return return_code;
}

err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_view, figure_t *figure)
{
    if (graphic_view == NULL || graphic_view->scene == NULL || figure == NULL)
    {
        return ERROR_UNCORRECT_PARAMS;
    }

    err_t  return_code = clean_graphic_scene(graphic_view->scene);

    if (return_code == SUCCESS)
    {
        size_t edges_count;

        return_code = get_figure_edges_count(&edges_count, figure);

        for (size_t i = 0; return_code == SUCCESS && i < edges_count; i++)
        {
            edge_t *edge = NULL;

            return_code = get_figure_edge_by_index(&edge, figure, i);

            if (return_code == SUCCESS)
                return_code = draw_one_edge_of_figure(graphic_view, figure, edge);
        }
    }

    return return_code;
}
