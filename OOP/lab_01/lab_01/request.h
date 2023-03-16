#ifndef REQUEST_H
#define REQUEST_H

#include "figure.h"
#include "error.h"
#include "graphicview.h"
#include "objectsizeparams.h"

enum requests {
    READ,
    MOVE,
    ROTATE,
    SCALE,
    DRAW,
    FREE
};

typedef enum requests request_type_t;


typedef struct
{
    char *path;
    move_coefficients_t *move_coefficients;
    scale_coefficients_t *scale_coefficients;
    rotate_coefficients_t *rotate_coefficients;
    graphic_view_t *grapgic_view;
    object_size_params_t *window_params;
} action_params_t;

action_params_t init_action_params(action_params_t params);
err_t read_action(figure_t *figure, action_params_t *params);
err_t scale_action(figure_t *figure, action_params_t *params);
err_t move_action(figure_t *figure, action_params_t *params);
err_t rotate_action(figure_t *figure, action_params_t *params);
err_t draw_action(figure_t *figure, action_params_t *params);
err_t free_action(figure_t *figure);

#endif // REQUEST_H
