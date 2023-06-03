#include "modeldata.h"

ModelData::ModelData(std::vector<Point> &points, std::vector<Edge> &edges):
    _points(points),
    _edges(edges),
    _center(Point(0, 0, 0)) {}

ModelData::ModelData(std::vector<Point> &points, std::vector<Edge> &edges, Point &center):
    _points(points),
    _edges(edges),
    _center(center) {}

const std::vector<Point> &ModelData::getPoints() const
{
    return this->_points;
}

const std::vector<Edge> &ModelData::getEdges() const
{
    return this->_edges;
}

const Point &ModelData::getCenter() const
{
    return this->_center;
}

ModelData &ModelData::addPoint(const Point &point)
{
    if (!this->_checkPointInModel(point))
    {
        this->_points.push_back(point);
        this->_updateCenter();
    }

    return (*this);
}

ModelData &ModelData::addEdge(const Edge &edge)
{
    if (!this->_checkEdgeInModel(edge))
    {
        this->addPoint(edge.getFirst());
        this->addPoint(edge.getSecond());

        this->_edges.push_back(edge);
    }

    return (*this);
}

ModelData &ModelData::_updateCenter()
{
    _center = Point(0, 0, 0);

    size_t count = 0;

    for (const auto &point : _points) {
        this->_center = this->_center + point;
        count++;
    }

    this->_center = Point(this->_center.getX() / count, this->_center.getY() / count, this->_center.getZ() / count);

    return (*this);
}

bool ModelData::_checkPointInModel(const Point &point)
{
    return std::find(this->_points.begin(), this->_points.end(), point) != this->_points.end();
}

bool ModelData::_checkEdgeInModel(const Edge &edge)
{
    return std::find(this->_edges.begin(), this->_edges.end(), edge) != this->_edges.end();
}

