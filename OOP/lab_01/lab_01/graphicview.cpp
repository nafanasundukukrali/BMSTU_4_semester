#include "graphicview.h"
#include "figure.h"
#include "handler.h"

graphic_view_t init_graphic_view(QGraphicsScene *scene, QPen pen)
{
    graphic_view_t graphic_view;

    graphic_view.scene = scene;
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
    return (graphic_scene != NULL && graphic_scene->scene != NULL);
}

static err_t get_drawing_coefficients(graphic_view_t *graphic_scene, figure_t *figure)
{
    if (!check_graphic_view_data_correctness(graphic_scene) || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double window_width, window_height;
    figure_configuration_t figure_params;

    err_t return_code = get_global_window_size_params_width(&window_height, &window_width);

    if (return_code == SUCCESS)
        return_code = get_figure_projection_width_height_params(&figure_params, figure);

    double kx = 0, ky = 0, figure_height, figure_width, figure_min_bottum_cord, figure_min_left_cord, k = 0, xm = 0, ym = 0;

    if (return_code == SUCCESS)
    {
        return_code = get_figure_height(&figure_params, &figure_height);

        if (return_code == SUCCESS)
            return_code = get_figure_width(&figure_params, &figure_width);

        if (return_code == SUCCESS)
            return_code = get_figure_min_bottum_cord(&figure_params, &figure_min_bottum_cord);

        if (return_code == SUCCESS)
            return_code = get_figure_min_left_cord(&figure_params, &figure_min_left_cord);

        if (return_code == SUCCESS)
        {
            ky = window_height / figure_height / 2;
            kx = window_width / figure_width / 2;
            k = fmin(kx, ky);
            xm = - k * figure_min_left_cord + k / k * window_width / 2;
            ym = - k * figure_min_bottum_cord + k / k * window_height / 2;
        }
    }

    view_coefficients_t coefficients = init_view_coefficients(k, xm, ym);

    if (return_code == SUCCESS)
        return_code = set_graph_coefficients(graphic_scene, &coefficients);

    return return_code;
}

typedef struct
{
    point_t *dst_point;
    point_t *src_point;
    scale_coefficients_t *scale_coefficients;
    move_coefficients_t *move_coefficients;
} modificate_point_for_graph_view_sizes_params_t;

static err_t prepare_figure_for_drawing(graphic_view_t *graphic_scene, figure_t *figure)
{
    if (graphic_scene == NULL || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    double k, xm, ym;

    err_t return_code = get_view_coefficients_k(&(graphic_scene->coefficient), &k);

    if (return_code == SUCCESS)
        return_code = get_view_coefficients_xm(&(graphic_scene->coefficient), &xm);

    if (return_code == SUCCESS)
        return_code = get_view_coefficients_xm(&(graphic_scene->coefficient), &ym);

    if (return_code == SUCCESS)
    {
        scale_coefficients_t scale_coefficiens = init_scale_coefficients(k, k, k);
        move_coefficients_t move_coefficients = init_move_coefficients(ym, ym, 0.0);

        action_params_t prepare_action_coefficients = init_prepare_figure_for_drawing_action_coefficients(figure,
                                                                                                                        &move_coefficients,
                                                                                                                        &scale_coefficiens);


        return_code = handler_action(PREPARE_FOR_DRAW, &prepare_action_coefficients);
    }

    return return_code;
}

err_t draw_one_edge_of_figure_by_index(graphic_view_t *graphic_view, figure_t *figure, const size_t index)
{
    if (graphic_view == NULL || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    edge_t *edge;
    point_t *start, *end;
    size_t start_index, end_index;

    err_t return_code = get_figure_edge_by_index(figure, &edge, index);

    if (return_code == SUCCESS)
        return_code = get_edge_start(edge, &start_index);

    if (return_code == SUCCESS)
        return_code = get_edge_end(edge, &end_index);

    if (return_code == SUCCESS)
        return_code = get_figure_point_by_index(figure, &start, start_index);

    if (return_code == SUCCESS)
        return_code = get_figure_point_by_index(figure, &end, end_index);

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
    if (!check_graphic_view_data_correctness(graphic_view) || figure == NULL)
        return ERROR_UNCORRECT_PARAMS;

    err_t return_code = get_drawing_coefficients(graphic_view, figure);

    figure_t buffer_figure = init_figure();

    if (return_code == SUCCESS)
        return_code = copy_figure_with_memory(figure, &buffer_figure);

    if (return_code == SUCCESS)
        return_code = prepare_figure_for_drawing(graphic_view, &buffer_figure);

    if (return_code == SUCCESS)
        return_code = clean_graphic_scene(graphic_view->scene);

    size_t edges_count;

    if (return_code == SUCCESS)
        return_code = get_figure_edges_count(&buffer_figure, &edges_count);

    for (size_t i = 0; return_code == SUCCESS && i < edges_count; i++)
        return_code = draw_one_edge_of_figure_by_index(graphic_view, &buffer_figure, i);

    free_figure_memory(&buffer_figure);

    return return_code;
}
