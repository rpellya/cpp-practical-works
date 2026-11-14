#pragma once
#ifndef GEOMETRY_FUNCTIONS_H
#define GEOMETRY_FUNCTIONS_H

#include "Point.h"
#include "Square.h"
#include <string>

// L4: Нахождение двух пар точек, которые определяют параллельные линии
bool getParallelLines(Point* points, int size, Point& p11, Point& p12, Point& p21, Point& p22);

// P3: Найти точку, сумма расстояний от которой до остальных точек множества минимальна
Point getClosestPoint(Point* points, int size);

// F4: Проверка пересечения двух квадратов Square (произвольная ориентация)
bool checkFigureCrossing(const Square& f1, const Square& f2);

// Функции ввода-вывода данных
double readDouble(const std::string& prompt);
int readInt(const std::string& prompt, int minValue, int maxValue);
Point inputPoint(const std::string& pointName);
Point* inputPointsArray(int& size);
void freePointsArray(Point*& points);
Square inputSquare(const std::string& squareName);
void printPointsArray(const Point* points, int size, const std::string& name);

#endif // GEOMETRY_FUNCTIONS_H
