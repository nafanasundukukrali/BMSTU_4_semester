#include "point.h"

Point::Point(Point &&point) noexcept
{
    this->_x = point._x;
    this->_y = point._y;
    this->_z = point._z;

    point.~Point();
}

Point &Point::operator = (Point &&point) noexcept
{
    this->_x = point._x;
    this->_y = point._y;
    this->_z = point._z;

    point.~Point();

    return *this;
}

bool Point::operator == (const Point &point) const noexcept
{
    return this->_x == point._x && this->_y == point._y && this->_z == point._z;
}

bool Point::operator != (const Point &point) const noexcept
{
    return !((*this) == point);
}

bool Point::equal(const Point &point) const noexcept
{
    return (*this) == point;
}

bool Point::noEqual(const Point &point) const noexcept
{
    return (*this) != point;
}

Point Point::operator + (const Point &point) const
{
    Point buffer(*this);

    buffer._x = this->_x + point._x;
    buffer._y = this->_y + point._y;
    buffer._z = this->_z + point._z;

    return buffer;
}

Point Point::operator - (const Point &point) const
{
    Point buffer(*this);

    buffer._x = this->_x - point._x;
    buffer._y = this->_y - point._y;
    buffer._z = this->_z - point._z;

    return buffer;
}

Point Point::sum(const Point &point) const
{
    return (*this) + point;
}

Point Point::sub(const Point &point) const
{
    return (*this) - point;
}

double Point::getX() const
{
    return this->_x;
}

double Point::getY() const
{
    return this->_y;
}

double Point::getZ() const
{
    return this->_z;
}

Point &Point::setX(double const x)
{
    this->_x = x;

    return *this;
}

Point &Point::setY(double const y)
{
    this->_y = y;

    return *this;
}

Point &Point::setZ(double const z)
{
    this->_z = z;

    return *this;
}
