#ifndef EDGE_H
#define EDGE_H

#include "point.h"

class Edge {
public:
    Edge(Point& point1, Point &point2): _point1(point1), _point2(point2) {};
    explicit Edge(const Edge &edge);
    Edge(Edge &&edge) noexcept;
    ~Edge() = default;

    bool operator == (const Edge& edge) const noexcept;
    bool isEqual(const Edge& edge);

    Point &getFirst() const;
    Point &getSecond() const;
    Edge &setFirst(const Point &point);
    Edge &setSecond(const Point &point);

private:
    Point &_point1;
    Point &_point2;
};

#endif // EDGE_H
