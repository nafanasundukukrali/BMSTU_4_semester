#include "testpoint.h"

#include "point.h"

void TestPoint::base_constructor()
{
    Point a(0.0, 1.0, 2.0);

    QVERIFY(a.getX() == 0 && a.getY() == 1 && a.getZ() == 2);
}

void TestPoint::copy_constructor()
{
    Point a(0.0, 1.0, 2.0);
    Point b(a);

    QVERIFY(a == b);
}

void TestPoint::move_constructor()
{
    Point a(Point(0, 0, 0));

    Point b(0, 0, 0);

    QVERIFY(a == b);
}

void TestPoint::sum()
{
    Point a(1, 2, 3);

    Point b(3, 2, 1);

    Point c(4, 4, 4);

    QVERIFY(a + b == c);
}

void TestPoint::sub()
{
    Point a(1, 2, 3);

    Point b(1, 2, 3);

    Point c(0, 0, 0);

    QVERIFY(a - b == c);
}

void TestPoint::getPointsData()
{
    Point a(0.0, 1.0, 2.0);

    QVERIFY(a.getX() == 0 && a.getY() == 1 && a.getZ() == 2);
}

void TestPoint::setPointsData()
{
    Point a(0.0, 1.0, 2.0), c(2, 3, 4);

    a.setX(2.0);
    a.setY(3.0);
    a.setZ(4.0);

    QVERIFY(a == c);
}
