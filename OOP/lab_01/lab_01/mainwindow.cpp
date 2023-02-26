#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fileio.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    connect(ui->choose_file_button, &QPushButton::released, this, &MainWindow::on_select_file_button_click);
    connect(ui->load_button, &QPushButton::released, this, &MainWindow::on_load_button_click);
    connect(ui->scale_button, &QPushButton::released, this, &MainWindow::on_scale_button_click);
    connect(ui->move_button, &QPushButton::released, this, &MainWindow::on_move_button_click);
    connect(ui->rotate_button, &QPushButton::released, this, &MainWindow::on_rotate_button_click);

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

void MainWindow::on_select_file_button_click()
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

void MainWindow::on_load_button_click()
{
    err_t return_code = SUCCESS;
    QString file_path = this->ui->path_line->text();

    if (file_path.isEmpty())
    {
        return_code = ERROR_NO_PATH;
    }
    else
    {
       FILE *file;
       char *file_path_char_string = file_path.toLocal8Bit().data();
       figure_t buffer_figure = init_figure();

       return_code = open_file_by_path(file_path_char_string, &file);

       if (return_code == SUCCESS)
           return_code = read_data_from_file(file, &buffer_figure);

       if (fclose(file))
           return_code = ERROR_CLOSE_FILE;

       if (return_code == SUCCESS)
            return_code = check_figure_data_correctness(&buffer_figure);

       if (return_code == SUCCESS)
       {
           if (!check_wether_figure_is_free(&figure))
               free_figure_memory(&figure);

           figure = buffer_figure;
       }
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

void MainWindow::on_scale_button_click()
{
    err_t return_code = SUCCESS;

    if (!downloadFigureStatus)
        return_code = ERROR_NO_LOADED_FIGURE;

    if (return_code == SUCCESS)
    {
        scale_coefficients_t scale_coefficients = init_scale_coefficients(ui->kx_box->value(),
                                                                          ui->ky_box->value(),
                                                                          ui->kz_box->value());

        return_code = scale_figure(&figure, &scale_coefficients);
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

        return_code = move_figure(&figure, &move_coefficients);
    }

    if (return_code == SUCCESS)
        return_code = draw_figure_orthogonal_projection(&graphicScene, &figure);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

void MainWindow::on_rotate_button_click()
{
    err_t return_code = SUCCESS;

    if (!downloadFigureStatus)
        return_code = ERROR_NO_LOADED_FIGURE;

    if (return_code == SUCCESS)
    {
        rotate_coefficients_t rotate_coefficients = init_rotate_coefficients(ui->ox_box->value(),
                                                                             ui->oy_box->value(),
                                                                             ui->oz_box->value());

        return_code = rotate_figure(&figure, &rotate_coefficients);
    }

    if (return_code == SUCCESS)
        return_code = draw_figure_orthogonal_projection(&graphicScene, &figure);

    if (return_code != SUCCESS)
        displayErrorMessage(return_code);
}

MainWindow::~MainWindow()
{
    free_figure_memory(&figure);
    delete ui;
}
