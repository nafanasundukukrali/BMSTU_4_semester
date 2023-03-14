#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "graphicview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    graphic_view_t graphicScene;
    bool downloadFigureStatus = false;
    object_size_params_t window_params;

    void on_select_file_button_click(void);
    void on_load_button_click(void);
    void on_scale_button_click(void);
    void on_move_button_click(void);
    void on_rotate_button_click(void);
    void connect_buttons_to_ui(void);

    ~MainWindow(void);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
