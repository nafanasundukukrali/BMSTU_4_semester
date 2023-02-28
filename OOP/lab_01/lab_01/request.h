#ifndef REQUEST_H
#define REQUEST_H

#include "figure.h"
#include "error.h"
#include "graphicview.h"

#include <QString>
#include <QGraphicsScene>

enum requests {
    READ,
    MOVE,
    ROTATE,
    SCALE
};

typedef enum requests request_t;

typedef struct
{
    QString *file_path;
    figure_t *figure;
    graphic_view_t *graphicScene;

} read_action_coefficients_t;

typedef struct
{
    scale_coefficients_t *coefficients;
    figure_t *figure;
} scale_action_coefficients_t;

typedef struct
{
    move_coefficients_t *coefficients;
    figure_t *figure;
} move_action_coefficients_t;

typedef struct
{
    rotate_coefficients_t *coefficients;
    figure_t *figure;
} rotate_action_coefficients_t;

err_t read_action(void *params);
err_t scale_action(void *params);
err_t move_action(void *params);
err_t rotate_action(void *params);

read_action_coefficients_t init_read_action_coefficients(QString *file_path, figure_t *figure, graphic_view_t *scene);
scale_action_coefficients_t init_scale_action_coefficients(figure_t *figure, scale_coefficients_t *coefficients);
move_action_coefficients_t init_move_action_coefficients(figure_t *figure, move_coefficients_t *coefficients);
rotate_action_coefficients_t init_rotate_action_coefficients(figure_t *figure, rotate_coefficients_t *coefficients);

#endif // REQUEST_H
