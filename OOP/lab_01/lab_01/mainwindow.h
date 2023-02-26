#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "figure.h"
#include "graphicview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    figure_t figure;
    bool downloadFigureStatus;
    graphic_view_t graphicScene;
    width_height_params_t params;

    MainWindow(QWidget *parent = nullptr);
    void on_select_file_button_click();
    void on_load_button_click();
    void on_scale_button_click();
    void on_move_button_click();
    void on_rotate_button_click();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
