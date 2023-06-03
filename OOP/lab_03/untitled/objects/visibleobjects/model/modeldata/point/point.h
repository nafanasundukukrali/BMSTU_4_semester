#ifndef POINT_H
#define POINT_H

#include <vector>

class Point
{
public:
    Point() = default;
    Point(const double x, const double y, const double z): _x(x), _y(y), _z(z) {};
    ~Point() noexcept = default;
    explicit Point(const Point &point) = default;
    Point(Point &&point) noexcept;

    Point &operator = (const Point &point) = default;
    Point &operator = (Point &&point) noexcept;

    bool operator == (const Point &point) const noexcept;
    bool operator != (const Point &point) const noexcept;
    bool equal(const Point &point) const noexcept;
    bool noEqual(const Point &point) const noexcept;

    Point operator + (const Point &point)  const;
    Point operator - (const Point &point)  const;
    Point sum(const Point &point) const;
    Point sub(const Point &point) const;

    double getX() const;
    double getY() const;
    double getZ() const;

    Point &setX(double const x);
    Point &setY(double const y);
    Point &setZ(double const z);
private:
    double _x = 0, _y = 0, _z = 0;
};

#endif // POINT_H
