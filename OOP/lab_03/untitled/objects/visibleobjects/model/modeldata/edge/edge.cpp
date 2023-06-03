#include "edge.h"

Edge::Edge(const Edge&edge): _point1(edge._point1), _point2(edge._point2) {};

Edge::Edge(Edge &&edge) noexcept: _point1(edge._point1), _point2(edge._point2)
{
    edge.~Edge();
}

bool Edge::operator == (const Edge& edge) const noexcept
{
    return this->_point1 == edge._point1 && this->_point2 == edge._point2;
}

bool Edge::isEqual(const Edge& edge)
{
    return (*this) == edge;
}

Point &Edge::getFirst() const
{
    return this->_point1;
}

Point &Edge::getSecond() const
{
    return this->_point2;
}

Edge &Edge::setFirst(const Point &point)
{
    this->_point1 = point;

    return (*this);
}

Edge &Edge::setSecond(const Point &point)
{
    this->_point2 = point;

    return (*this);
}
