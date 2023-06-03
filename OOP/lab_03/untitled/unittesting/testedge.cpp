#include "testedge.h"

#include "edge.h"

void TestEdge::base_constructor()
{
    Point a1(0, 0, 0);
    Point a2(1, 1, 1);

    Edge a(a1, a2);

    QVERIFY(a.getFirst() == a1 && a.getSecond() == a2);
}

void TestEdge::copy_constructor()
{
    Point a1(0, 0, 0);
    Point a2(1, 1, 1);

    Edge a(a1, a2);
    Edge b(a);

    QVERIFY(a == b);
}

void TestEdge::move_constructor()
{
    Point a1(0, 0, 0);
    Point a2(1, 1, 1);

    Edge a(Edge(a1, a2));
    Edge b(a1, a2);

    QVERIFY(a == b);
}

void TestEdge::getFirstAndSecond()
{
    Point a1(0, 0, 0);
    Point a2(1, 1, 1);

    Edge a(a1, a2);

    QVERIFY(a.getFirst() == a1 && a.getSecond() == a2);
}

void TestEdge::setFirstAndSecond()
{
    Point a1(0, 0, 0);
    Point a2(1, 1, 1);
    Point a3(2, 3, 4);
    Point a4(5, 6, 7);


    Edge a(a1, a2);
    a.setFirst(a3);
    a.setSecond(a4);

    QVERIFY(a.getFirst() == a3 && a.getSecond() == a4);
}
