#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>

#include "point.h"
#include "edge.h"

class ModelData {
public:
    ModelData() = default;
    explicit ModelData(std::vector<Point> &points, std::vector<Edge> &edges);
    ModelData(std::vector<Point> &points, std::vector<Edge> &edges, Point &center);
    ~ModelData() = default;

    const std::vector<Point> &getPoints() const;
    const std::vector<Edge> &getEdges() const;
    const Point &getCenter() const;

    ModelData &addPoint(const Point &point);
    ModelData &addEdge(const Edge &edge);
private:
    std::vector<Point> _points;
    std::vector<Edge> _edges;
    Point _center;

    ModelData &_updateCenter();
    bool _checkPointInModel(const Point &point);
    bool _checkEdgeInModel(const Edge &edge);
};

#endif // MODELDATA_H
