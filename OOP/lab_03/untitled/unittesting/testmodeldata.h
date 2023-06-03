#ifndef TESTMODELDATA_H
#define TESTMODELDATA_H

#include <QTest>

class TestModelData: public QObject
{
    Q_OBJECT
private slots:
    void constructor_center();
    void constructor_no_center();

    void getPoints();
    void getEdges();
    void getCenter();

    void addPoint();
    void addEdge();
    void addSamePointsAndEdges();

    void updateCenter();
};

#endif // TESTMODELDATA_H
