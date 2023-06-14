#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("ЩЕРБИНСКИЙ ЛИФТОСТРОИТЕЛЬНЫЙ ЗАВОД"));
    w.show();
    return a.exec();
}
