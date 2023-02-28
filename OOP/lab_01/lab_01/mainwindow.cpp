#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "handler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_buttons_to_ui();
    setFixedSize(width(), height());

    downloadFigureStatus = false;
    figure = init_figure();

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::white));

    QPen pen;
    pen.setColor(QColorConstants::Svg::pink);
    pen.setWidth(3);

    params = init_width_height_params(ui->graphicsView->width(),
                                      ui->graphicsView->height());

    graphicScene = init_graphic_view(ui->graphicsView->scene(), &params, pen);
}

void MainWindow::connect_buttons_to_ui(void)
{
    connect(ui->choose_file_button, &QPushButton::released, this, &MainWindow::on_select_file_button_click);
    connect(ui->load_button, &QPushButton::released, this, &MainWindow::on_load_button_click);
    connect(ui->scale_button, &QPushButton::released, this, &MainWindow::on_scale_button_click);
    connect(ui->move_button, &QPushButton::released, this, &MainWindow::on_move_button_click);
    connect(ui->rotate_button, &QPushButton::released, this, &MainWindow::on_rotate_button_click);
}

void MainWindow::on_select_file_button_click(void)
{
    err_t return_code = SUCCESS;

    QString file_path = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath());

    if (!file_path.isEmpty())
        this->ui->path_line->setText(file_path);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

void MainWindow::on_load_button_click(void)
{
    err_t return_code = SUCCESS;
    QString file_path = this->ui->path_line->text();

    if (file_path.isEmpty())
    {
        return_code = ERROR_NO_PATH;
    }
    else
    {
        read_action_coefficients_t read_coefficients = init_read_action_coefficients(&file_path, &figure, &graphicScene);
        return_code = handler_action(READ, &read_coefficients);
    }

    if (return_code != SUCCESS)
    {
        displayErrorMessage(return_code);
    }
    else
    {
        draw_figure_orthogonal_projection(&graphicScene, &figure);
        downloadFigureStatus = true;
    }
}

void MainWindow::on_scale_button_click(void)
{
    err_t return_code = SUCCESS;

    if (!downloadFigureStatus)
        return_code = ERROR_NO_LOADED_FIGURE;

    if (return_code == SUCCESS)
    {
        scale_coefficients_t scale_coefficients = init_scale_coefficients(ui->kx_box->value(),
                                                                          ui->ky_box->value(),
                                                                          ui->kz_box->value());
        scale_action_coefficients_t action_coefficients = init_scale_action_coefficients(&figure, &scale_coefficients);

        return_code = scale_action(&action_coefficients);
    }

    if (return_code == SUCCESS)
        return_code = draw_figure_orthogonal_projection(&graphicScene, &figure);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

void MainWindow::on_move_button_click()
{
    err_t return_code = SUCCESS;

    if (!downloadFigureStatus)
        return_code = ERROR_NO_LOADED_FIGURE;

    if (return_code == SUCCESS)
    {
        move_coefficients_t move_coefficients = init_move_coefficients(ui->dx_box->value(),
                                                                       ui->dy_box->value(),
                                                                       ui->dz_box->value());
        move_action_coefficients_t action_params = init_move_action_coefficients(&figure, &move_coefficients);

        return_code = move_action(&action_params);
    }

    if (return_code == SUCCESS)
        return_code = draw_figure_orthogonal_projection(&graphicScene, &figure);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

void MainWindow::on_rotate_button_click(void)
{
    err_t return_code = SUCCESS;

    if (!downloadFigureStatus)
        return_code = ERROR_NO_LOADED_FIGURE;

    if (return_code == SUCCESS)
    {
        rotate_coefficients_t rotate_coefficients = init_rotate_coefficients(ui->ox_box->value(),
                                                                             ui->oy_box->value(),
                                                                             ui->oz_box->value());

        rotate_action_coefficients_t action_params = init_rotate_action_coefficients(&figure, &rotate_coefficients);

        return_code = rotate_action(&action_params);
    }

    if (return_code == SUCCESS)
        return_code = draw_figure_orthogonal_projection(&graphicScene, &figure);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

MainWindow::~MainWindow(void)
{
    free_figure_memory(&figure);
    delete ui;
}
