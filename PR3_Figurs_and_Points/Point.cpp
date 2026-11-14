#include "Point.h"
#include <cmath>
#include <iostream>

Point::Point() : m_x(0.0), m_y(0.0) {}

Point::Point(double x, double y) : m_x(x), m_y(y) {}

double Point::getX() const {
    return m_x;
}

double Point::getY() const {
    return m_y;
}

void Point::print() const {
    std::cout << "(" << m_x << "; " << m_y << ")";
}

double distance(const Point& p1, const Point& p2) {
    double dx = p1.getX() - p2.getX();
    double dy = p1.getY() - p2.getY();
    return std::sqrt(dx * dx + dy * dy);
}
