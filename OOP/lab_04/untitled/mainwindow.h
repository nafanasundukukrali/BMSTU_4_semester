#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include "elevator.h"
#include <memory>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
private:
    Elevator _elevator;
    std::unique_ptr<QVBoxLayout> _layout;
};

#endif // MAINWINDOW_H
