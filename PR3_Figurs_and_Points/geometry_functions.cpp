#include "geometry_functions.h"
#include <iostream>
#include <cmath>
#include <string>
#include <new>

// L4: Нахождение двух пар точек, определяющих параллельные линии
bool getParallelLines(Point* points, int size, Point& p11, Point& p12, Point& p21, Point& p22) {
    if (points == nullptr || size < 4) {
        return false;
    }

    // Перебираем первую пару точек (i, j) для первой прямой
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double dx1 = points[j].getX() - points[i].getX();
            double dy1 = points[j].getY() - points[i].getY();

            // Пропускаем, если точки совпадают (не задают прямую)
            if (dx1 == 0.0 && dy1 == 0.0) {
                continue;
            }

            // Перебираем вторую пару точек (k, l) для второй прямой
            for (int k = 0; k < size; ++k) {
                // Точка k не должна совпадать с первой парой
                if (k == i || k == j) continue;

                for (int l = k + 1; l < size; ++l) {
                    // Точка l не должна совпадать с первой парой
                    if (l == i || l == j) continue;

                    double dx2 = points[l].getX() - points[k].getX();
                    double dy2 = points[l].getY() - points[k].getY();

                    // Пропускаем совпадающие точки второй пары
                    if (dx2 == 0.0 && dy2 == 0.0) {
                        continue;
                    }

                    // Проверяем параллельность с точностью 0.0001 для компенсации погрешностей double
                    if (std::fabs(dx1 * dy2 - dy1 * dx2) < 0.0001) {
                        p11 = points[i];
                        p12 = points[j];
                        p21 = points[k];
                        p22 = points[l];
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// P3: Точка с минимальной суммой расстояний до остальных точек множества
Point getClosestPoint(Point* points, int size) {
    if (points == nullptr || size <= 0) {
        return Point(0.0, 0.0);
    }
    if (size == 1) {
        return points[0];
    }

    int bestIndex = 0;
    double minTotalDistance = -1.0;

    // Для каждой точки считаем сумму расстояний до всех остальных
    for (int i = 0; i < size; ++i) {
        double currentSum = 0.0;

        for (int j = 0; j < size; ++j) {
            // Не считаем расстояние от точки до самой себя
            if (i != j) {
                currentSum += distance(points[i], points[j]);
            }
        }

        // Запоминаем точку с наименьшей суммой расстояний
        if (minTotalDistance < 0.0 || currentSum < minTotalDistance) {
            minTotalDistance = currentSum;
            bestIndex = i;
        }
    }

    return points[bestIndex];
}

// F4: Проверка пересечения двух квадратов по методу разделяющих осей (SAT)
bool checkFigureCrossing(const Square& f1, const Square& f2) {
    if (!f1.isValid() || !f2.isValid()) {
        return false;
    }

    const Point* pts1 = f1.getPoints();
    const Point* pts2 = f2.getPoints();

    // 1. Проверяем 4 оси, перпендикулярные сторонам первого квадрата
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        double edgeX = pts1[next].getX() - pts1[i].getX();
        double edgeY = pts1[next].getY() - pts1[i].getY();

        // Перпендикуляр (нормаль) к ребру
        double axisX = -edgeY;
        double axisY = edgeX;

        // Ищем интервал проекции первого квадрата на эту ось
        double min1 = pts1[0].getX() * axisX + pts1[0].getY() * axisY;
        double max1 = min1;
        for (int k = 1; k < 4; ++k) {
            double proj = pts1[k].getX() * axisX + pts1[k].getY() * axisY;
            if (proj < min1) min1 = proj;
            if (proj > max1) max1 = proj;
        }

        // Ищем интервал проекции второго квадрата на эту же ось
        double min2 = pts2[0].getX() * axisX + pts2[0].getY() * axisY;
        double max2 = min2;
        for (int k = 1; k < 4; ++k) {
            double proj = pts2[k].getX() * axisX + pts2[k].getY() * axisY;
            if (proj < min2) min2 = proj;
            if (proj > max2) max2 = proj;
        }

        // Если проекции на этой оси не перекрываются — квадраты не пересекаются
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    // 2. Проверяем 4 оси, перпендикулярные сторонам второго квадрата
    for (int j = 0; j < 4; ++j) {
        int next = (j + 1) % 4;
        double edgeX = pts2[next].getX() - pts2[j].getX();
        double edgeY = pts2[next].getY() - pts2[j].getY();

        double axisX = -edgeY;
        double axisY = edgeX;

        // Проекция первого квадрата
        double min1 = pts1[0].getX() * axisX + pts1[0].getY() * axisY;
        double max1 = min1;
        for (int k = 1; k < 4; ++k) {
            double proj = pts1[k].getX() * axisX + pts1[k].getY() * axisY;
            if (proj < min1) min1 = proj;
            if (proj > max1) max1 = proj;
        }

        // Проекция второго квадрата
        double min2 = pts2[0].getX() * axisX + pts2[0].getY() * axisY;
        double max2 = min2;
        for (int k = 1; k < 4; ++k) {
            double proj = pts2[k].getX() * axisX + pts2[k].getY() * axisY;
            if (proj < min2) min2 = proj;
            if (proj > max2) max2 = proj;
        }

        // Если проекции не перекрываются — квадраты не пересекаются
        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    // Если ни одна ось не разделила проекции — фигуры пересекаются
    return true;
}

double readDouble(const std::string& prompt) {
    double value;
    // Цикл до корректного ввода числа
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            return 0.0;
        }
        // Сброс флага ошибки и очистка буфера при неверном вводе
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Ошибка: некорректный ввод числа. Повторите попытку.\n";
    }
}

int readInt(const std::string& prompt, int minValue, int maxValue) {
    int value;
    // Цикл проверки диапазона числа
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            std::cout << "Ошибка: введите число от " << minValue << " до " << maxValue << ".\n";
            continue;
        }
        if (std::cin.eof()) {
            return minValue;
        }
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Ошибка: некорректный ввод числа. Повторите попытку.\n";
    }
}

Point inputPoint(const std::string& pointName) {
    std::cout << "  Ввод точки " << pointName << ":\n";
    double x = readDouble("    Координата X: ");
    double y = readDouble("    Координата Y: ");
    return Point(x, y);
}

Point* inputPointsArray(int& size) {
    size = readInt("Введите количество точек (минимум 1): ", 1, 100000);
    // Безопасное выделение памяти без генерации исключений (std::nothrow)
    Point* arr = new (std::nothrow) Point[size];
    if (arr == nullptr) {
        std::cout << "Ошибка: не удалось выделить память под массив точек!\n";
        size = 0;
        return nullptr;
    }

    // Поточечный ввод координат в массив
    for (int i = 0; i < size; ++i) {
        std::cout << "Точка [" << i << "]:\n";
        double x = readDouble("  X: ");
        double y = readDouble("  Y: ");
        // Если ввод прерван, освобождаем выделенную память
        if (std::cin.eof()) {
            delete[] arr;
            size = 0;
            return nullptr;
        }
        arr[i] = Point(x, y);
    }
    return arr;
}

void freePointsArray(Point*& points) {
    if (points != nullptr) {
        delete[] points;
        points = nullptr;
    }
}

Square inputSquare(const std::string& squareName) {
    std::cout << "\nВвод фигуры " << squareName << " (Квадрат):\n";
    std::cout << "Введите 4 точки в произвольном порядке:\n";
    Point p1 = inputPoint("P1");
    Point p2 = inputPoint("P2");
    Point p3 = inputPoint("P3");
    Point p4 = inputPoint("P4");

    Square sq(p1, p2, p3, p4);
    // Проверяем корректность созданной фигуры
    if (!sq.isValid()) {
        std::cout << "Внимание: введенные точки не образуют квадрат!\n";
    } else {
        std::cout << "Квадрат успешно создан.\n";
    }
    return sq;
}

void printPointsArray(const Point* points, int size, const std::string& name) {
    if (points == nullptr || size <= 0) {
        std::cout << "Массив точек " << name << " пуст (не задан).\n";
        return;
    }

    std::cout << "Массив точек " << name << " (всего " << size << "):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "  [" << i << "] ";
        points[i].print();
        std::cout << "\n";
    }
}
