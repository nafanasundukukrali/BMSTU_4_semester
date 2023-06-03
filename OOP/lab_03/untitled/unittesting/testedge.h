#ifndef TESTEDGE_H
#define TESTEDGE_H

#include <QTest>

class TestEdge: public QObject
{
    Q_OBJECT
private slots:
    void base_constructor();
    void copy_constructor();
    void move_constructor();

    void getFirstAndSecond();
    void setFirstAndSecond();
};

#endif // TESTEDGE_H
