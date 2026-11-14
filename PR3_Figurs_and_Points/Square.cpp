#include "Square.h"
#include <cmath>
#include <iostream>

Square::Square() : m_side(1.0), m_isValid(true) {
    m_points[0] = Point(0.0, 0.0);
    m_points[1] = Point(1.0, 0.0);
    m_points[2] = Point(1.0, 1.0);
    m_points[3] = Point(0.0, 1.0);
}

Square::Square(Point p1, Point p2, Point p3, Point p4) {
    // Проверяем 4 точки и упорядочиваем их
    if (!initFromPoints(p1, p2, p3, p4)) {
        m_points[0] = p1;
        m_points[1] = p2;
        m_points[2] = p3;
        m_points[3] = p4;
        m_side = 0.0;
        m_isValid = false;
    }
}

// Квадрат расстояния между точками
static double distanceSquared(const Point& a, const Point& b) {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return dx * dx + dy * dy;
}

// Проверка и упорядочивание 4 точек квадрата
bool Square::initFromPoints(Point p1, Point p2, Point p3, Point p4) {
    Point pts[4] = { p1, p2, p3, p4 };

    // 6 попарных расстояний между 4 точками
    double dSq[6];
    int pairIndices[6][2] = {
        {0, 1}, {0, 2}, {0, 3},
        {1, 2}, {1, 3}, {2, 3}
    };

    // Считаем все 6 попарных расстояний
    for (int i = 0; i < 6; ++i) {
        dSq[i] = distanceSquared(pts[pairIndices[i][0]], pts[pairIndices[i][1]]);
    }

    // Сортируем расстояния по возрастанию вставками
    for (int i = 1; i < 6; ++i) {
        double key = dSq[i];
        int j = i - 1;
        while (j >= 0 && dSq[j] > key) {
            dSq[j + 1] = dSq[j];
            --j;
        }
        dSq[j + 1] = key;
    }

    double s = dSq[0]; // Квадрат длины стороны

    // Если сторона 0 — точки совпадают
    if (s <= 0.0001) {
        return false;
    }

    // В квадрате 4 стороны должны быть равны s
    for (int i = 1; i < 4; ++i) {
        if (std::fabs(dSq[i] - s) > 0.0001) {
            return false;
        }
    }

    // В квадрате 2 диагонали должны быть равны 2*s
    if (std::fabs(dSq[4] - 2.0 * s) > 0.0001 ||
        std::fabs(dSq[5] - 2.0 * s) > 0.0001) {
        return false;
    }

    // Упорядочиваем вершины: берем p0 и ищем противоположную вершину
    Point p0 = pts[0];
    Point pOpposite;
    Point pAdjA, pAdjB;
    bool foundOpposite = false;
    bool foundA = false;

    // Ищем противоположную вершину (расстояние до нее = диагональ 2*s)
    for (int i = 1; i < 4; ++i) {
        double d = distanceSquared(p0, pts[i]);
        // Проверяем, является ли точка диагональной
        if (std::fabs(d - 2.0 * s) <= 0.0001) {
            pOpposite = pts[i];
            foundOpposite = true;
        } else {
            // Иначе это одна из двух соседних вершин
            if (!foundA) {
                pAdjA = pts[i];
                foundA = true;
            } else {
                pAdjB = pts[i];
            }
        }
    }

    if (!foundOpposite) {
        return false;
    }

    // Определяем порядок обхода по знаку косого произведения
    double uX = pAdjA.getX() - p0.getX();
    double uY = pAdjA.getY() - p0.getY();
    double vX = pAdjB.getX() - p0.getX();
    double vY = pAdjB.getY() - p0.getY();

    double cross = uX * vY - uY * vX;
    Point p1Ordered, p3Ordered;
    // Если поворот против часовой стрелки
    if (cross > 0) {
        p1Ordered = pAdjA;
        p3Ordered = pAdjB;
    } else {
        // Иначе меняем вершины местами для правильного обхода
        p1Ordered = pAdjB;
        p3Ordered = pAdjA;
    }

    m_points[0] = p0;
    m_points[1] = p1Ordered;
    m_points[2] = pOpposite;
    m_points[3] = p3Ordered;
    m_side = std::sqrt(s);
    m_isValid = true;

    return true;
}

Point* Square::getPoints() {
    return m_points;
}

const Point* Square::getPoints() const {
    return m_points;
}

double Square::getArea() const {
    if (!m_isValid) return 0.0;
    return m_side * m_side;
}

double Square::getPerimeter() const {
    if (!m_isValid) return 0.0;
    return 4.0 * m_side;
}

double Square::getSide() const {
    return m_side;
}

bool Square::isValid() const {
    return m_isValid;
}

void Square::print() const {
    if (!m_isValid) {
        std::cout << "Квадрат невалидный (заданные точки не образуют квадрат):\n";
        for (int i = 0; i < 4; ++i) {
            std::cout << "  [" << i << "] ";
            m_points[i].print();
            std::cout << "\n";
        }
        return;
    }

    std::cout << "Квадрат (сторона = " << m_side
              << ", периметр = " << getPerimeter()
              << ", площадь = " << getArea() << "):\n";
    std::cout << "  Вершины:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "    [" << i << "] ";
        m_points[i].print();
        std::cout << "\n";
    }
}
