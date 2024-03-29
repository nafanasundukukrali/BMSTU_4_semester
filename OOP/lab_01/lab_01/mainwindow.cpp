#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "handler.h"
#include "errormessagedialoge.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_buttons_to_ui();
    setFixedSize(width(), height());

    init_object_size_params(&window_params, width(), height());

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, ui->graphicsView->width()-10, ui->graphicsView->height()-10);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::white));
    downloadFigureStatus = false;

    QPen pen;
    pen.setColor(QColorConstants::Svg::pink);
    pen.setWidth(3);

    graphicScene = init_graphic_view(ui->graphicsView->scene(), pen);
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
        action_params_t read_coefficients = init_action_params({
                                                                   .path = file_path.toLocal8Bit().data(),
                                                                   .window_params = &window_params
                                                               });

        return_code = handler_action(READ, &read_coefficients);
    }

    if (return_code != SUCCESS)
    {
        displayErrorMessage(return_code);
    }
    else
    {
        action_params_t params = init_action_params({
                                                        .grapgic_view = &graphicScene,
                                                    });

        return_code = handler_action(DRAW, &params);
    }

    if (return_code == SUCCESS)
        downloadFigureStatus = true;
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
        action_params_t action_coefficients = init_action_params({.scale_coefficients = &scale_coefficients});

        return_code = handler_action(SCALE, &action_coefficients);
    }

    if (return_code == SUCCESS)
    {
        action_params_t params = init_action_params({
                                                        .grapgic_view = &graphicScene,
                                                    });

        return_code = handler_action(DRAW, &params);
    }

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
        action_params_t action_params = init_action_params({.move_coefficients = &move_coefficients});

        return_code = handler_action(MOVE, &action_params);
    }

    if (return_code == SUCCESS)
    {
        action_params_t params = init_action_params({
                                                        .grapgic_view = &graphicScene,
                                                    });

        return_code = handler_action(DRAW, &params);
    }

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

        action_params_t action_params = init_action_params({.rotate_coefficients =  &rotate_coefficients});

        return_code = handler_action(ROTATE, &action_params);
    }

    if (return_code == SUCCESS)
    {
        action_params_t params = init_action_params({
                                                        .grapgic_view = &graphicScene,
                                                    });

        return_code = handler_action(DRAW, &params);
    }

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

MainWindow::~MainWindow(void)
{
    handler_action(FREE, NULL);
    delete ui;
}
