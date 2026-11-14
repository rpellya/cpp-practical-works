#pragma once
#ifndef SQUARE_H
#define SQUARE_H

#include "Point.h"

class Square {
private:
    Point m_points[4];
    double m_side;
    bool m_isValid;

    bool initFromPoints(Point p1, Point p2, Point p3, Point p4);

public:
    Square();
    Square(Point p1, Point p2, Point p3, Point p4);

    Point* getPoints();
    const Point* getPoints() const;

    double getArea() const;
    double getPerimeter() const;

    double getSide() const;
    bool isValid() const;
    void print() const;
};

#endif // SQUARE_H
