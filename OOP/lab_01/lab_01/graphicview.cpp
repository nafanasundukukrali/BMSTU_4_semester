#include "graphicview.h"
#include "figure.h"

graphic_view_t init_graphic_view(QGraphicsScene *scene, width_height_params_t *params, QPen pen)
{
    graphic_view_t graphic_view;

    graphic_view.scene = scene;
    graphic_view.window_params = params;
    graphic_view.pen = pen;

    return graphic_view;
}

static err_t set_graph_coefficients(graphic_view_t *graphic_view, view_coefficients_t *coefficients)
{
    if (graphic_view == NULL || coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    graphic_view->coefficient = *coefficients;

    return SUCCESS;
}

bool check_graphic_view_data_correctness(graphic_view_t *graphic_scene)
{
    return (graphic_scene != NULL && graphic_scene->scene != NULL &&
            graphic_scene->window_params != NULL);
}

static err_t get_drawing_coefficients(graphic_view_t *graphic_scene, figure_t *figure)
{
    if (!check_graphic_view_data_correctness(graphic_scene) || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    figure_configuration_t figure_params = get_figure_projection_width_height_params(*figure);
    view_coefficients_t coefficients;

    double kx = 0, ky = 0;

    if (figure_params.object_params.window_height != 0 &&
            figure_params.object_params.window_width != 0)
    {
        ky = graphic_scene->window_params->window_height / (figure_params.object_params.window_height) / 2;
        kx = graphic_scene->window_params->window_width / (figure_params.object_params.window_width) / 2;

        coefficients.xm = - coefficients.k * (figure_params.min_left_cord) +
                coefficients.k / coefficients.k * graphic_scene->window_params->window_width / 2;
        coefficients.ym = - coefficients.k * (figure_params.min_bottum_cord) +
                coefficients.k / coefficients.k * graphic_scene->window_params->window_height / 2;

        coefficients.k = fmin(kx, ky);
    }
    else
    {
        coefficients.k = 0;
        coefficients.xm = 0;
        coefficients.ym = 0;
    }

    return set_graph_coefficients(graphic_scene, &coefficients);
}

typedef struct
{
    point_t *dst_point;
    point_t *src_point;
    scale_coefficients_t *scale_coefficients;
    move_coefficients_t *move_coefficients;
} modificate_point_for_graph_view_sizes_params_t;

static err_t modificate_point_for_graph_view_sizes(modificate_point_for_graph_view_sizes_params_t params)
{
    if (params.dst_point == NULL ||
            params.src_point == NULL ||
            params.move_coefficients == NULL ||
            params.scale_coefficients == NULL)
        return ERROR_UNCORRECT_PARAMS;

    point_t buffer_point = *params.dst_point;
    err_t return_code = scale_point_coords(&buffer_point, params.src_point, params.scale_coefficients);

    if (return_code == SUCCESS)
        return_code = move_point_coords(&buffer_point, &buffer_point, params.move_coefficients);

    if (return_code == SUCCESS)
        *(params.dst_point) = buffer_point;

    return return_code;
}

static err_t draw_figure_line(graphic_view_t *graphic_scene,
                              figure_t *figure, size_t line_index)
{
    if (graphic_scene == NULL ||
            figure == NULL || line_index >= figure->edges_array_length)
        return ERROR_UNCORRECT_PARAMS;

    scale_coefficients_t scale_coefficiens = init_scale_coefficients(graphic_scene->coefficient.k,
                                                                     graphic_scene->coefficient.k,
                                                                     graphic_scene->coefficient.k);
    move_coefficients_t move_coefficients = init_move_coefficients(graphic_scene->coefficient.xm,
                                                                   graphic_scene->coefficient.ym,
                                                                   0.0);

    point_t draw_point_start, draw_point_end;

    err_t return_code = modificate_point_for_graph_view_sizes({&draw_point_start,
                                           &(figure->points_array[figure->edges_array[line_index].start]),
                                            &scale_coefficiens, &move_coefficients});

    if (return_code == SUCCESS)
        return_code = modificate_point_for_graph_view_sizes({&draw_point_end,
                                         &(figure->points_array[figure->edges_array[line_index].end]),
                &scale_coefficiens, &move_coefficients});

    if (return_code == SUCCESS)
        graphic_scene->scene->addLine(draw_point_start.x,
                                      graphic_scene->window_params->window_height - draw_point_start.y,
                                      draw_point_end.x,
                                      graphic_scene->window_params->window_height - draw_point_end.y, graphic_scene->pen);

    return return_code;
}

err_t draw_figure_orthogonal_projection(graphic_view_t *graphic_scene, figure_t *figure)
{
    if (!check_graphic_view_data_correctness(graphic_scene) || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = get_drawing_coefficients(graphic_scene, figure);

    if (return_code == SUCCESS)
    {
        graphic_scene->scene->clear();

        for (size_t i = 0; return_code == SUCCESS &&
             i < figure->edges_array_length; i++)
            return_code = draw_figure_line(graphic_scene, figure, i);
    }

    return return_code;
}
