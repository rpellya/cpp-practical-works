#pragma once
#ifndef POINT_H
#define POINT_H

class Point {
private:
    double m_x;
    double m_y;

public:
    Point();
    Point(double x, double y);

    double getX() const;
    double getY() const;

    void print() const;
};

double distance(const Point& p1, const Point& p2);

#endif // POINT_H
