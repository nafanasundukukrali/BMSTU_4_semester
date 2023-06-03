#ifndef TESTPOINT_H
#define TESTPOINT_H

#include <QTest>

class TestPoint: public QObject
{
    Q_OBJECT
private slots:
    void base_constructor();
    void copy_constructor();
    void move_constructor();

    void sum();
    void sub();
    void getPointsData();
    void setPointsData();
};

#endif // TESTPOINT_H
