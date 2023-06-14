#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    this->setFixedSize(500, 500);
    this->_layout= std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->centralwidget->setLayout(this->_layout.get());
    this->_layout->addWidget(this->_elevator.widget());
}

