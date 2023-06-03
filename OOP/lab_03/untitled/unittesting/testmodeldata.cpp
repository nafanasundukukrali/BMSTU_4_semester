#include "testmodeldata.h"

#include "modeldata.h"
#include <vector>

void TestModelData::constructor_center()
{
    Point a1(0, 1, 2), a2(3, 4, 5);

    std::vector<Point> points;
    points.push_back(a1);
    points.push_back(a2);
    Edge edge (a1, a2);
    std::vector<Edge> edges;
    edges.push_back(edge);
    Point center(2, 6, 7);

    ModelData model(points, edges, center);

    QVERIFY(model.getPoints() == points && model.getEdges() == edges && model.getCenter() == center);
}

void TestModelData::constructor_no_center()
{
    Point a1(0, 1, 2), a2(3, 4, 5);

    std::vector<Point> points;
    points.push_back(a1);
    points.push_back(a2);
    std::vector<Edge> edges = {Edge(a1, a2)};
    Point center(0, 0, 0);
    ModelData model(points, edges);

    QVERIFY(model.getPoints() == points && model.getEdges() == edges && model.getCenter() == center);
}

void TestModelData::getPoints() {};
void TestModelData::getEdges() {};
void TestModelData::getCenter() {};

void TestModelData::addPoint()
{
    Point a1(0, 1, 2), a2(3, 4, 5), a3(6, 7, 8);

    std::vector<Point> points;
    points.push_back(a1);
    points.push_back(a2);
    std::vector<Point> points2;
    points2.push_back(a1);
    points2.push_back(a2);
    points2.push_back(a3);
    std::vector<Edge> edges = {Edge(a1, a2)};
    ModelData model(points, edges);
    model.addPoint(a3);
    QVERIFY(model.getPoints() == points2);
}

void TestModelData::addEdge()
{
    Point a1(0, 1, 2), a2(3, 4, 5), a3(6, 7, 8), a4(9, 10, 11);

    std::vector<Point> points;
    points.push_back(a1);
    points.push_back(a2);
    std::vector<Point> points2;
    points2.push_back(a1);
    points2.push_back(a2);
    points2.push_back(a3);
    std::vector<Edge> edges = {Edge(a1, a2)};
    std::vector<Edge> edges2 = {Edge(a1, a2), Edge(a3, a4)};
    ModelData model(points, edges);
    Edge edge(a3, a4);
    model.addEdge(edge);
    QVERIFY(model.getEdges() == edges2);
}

void TestModelData::addSamePointsAndEdges()
{
    Point a1(0, 1, 2), a2(3, 4, 5), a3(6, 7, 8), a4(9, 10, 11);

    std::vector<Point> points;
    points.push_back(a1);
    points.push_back(a2);
    std::vector<Point> points2;
    points2.push_back(a1);
    points2.push_back(a2);
    std::vector<Edge> edges = {Edge(a1, a2)};
    std::vector<Edge> edges2 = {Edge(a1, a2)};
    ModelData model(points, edges);
    Edge edge(a3, a4);
    model.addEdge(Edge(a1, a2));
    model.addPoint(a1);
    QVERIFY(model.getPoints() == points2 && model.getEdges() == edges2);
}

void TestModelData::updateCenter() {};
