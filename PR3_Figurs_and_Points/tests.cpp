#include "tests.h"
#include <iostream>
#include <string>
#include <cmath>
#include "Point.h"
#include "Square.h"
#include "geometry_functions.h"

// Функция проверки утверждения с выводом ожидаемого и полученного ответов
static void assertTest(const std::string& testName, bool condition, const std::string& expected, const std::string& actual, int& passed, int& failed) {
    if (condition) {
        std::cout << "  [PASS] " << testName << "\n";
        std::cout << "         Ожидаемый ответ:  " << expected << "\n";
        std::cout << "         Полученный ответ: " << actual << "\n";
        passed++;
    } else {
        std::cout << "  [FAIL] " << testName << "\n";
        std::cout << "         Ожидаемый ответ:  " << expected << "\n";
        std::cout << "         Полученный ответ: " << actual << "\n";
        failed++;
    }
}

static std::string boolToString(bool b) {
    return b ? "true" : "false";
}

void runEquivalencePartitioningTests() {
    int passed = 0;
    int failed = 0;

    std::cout << "\nЗапуск набора тестов (Equivalence Partitioning & Boundary Value Analysis)\n";

    // [1] Тесты класса Point
    std::cout << "\n[1] Тесты класса Point: конструкторы, координаты, distance\n";
    {
        Point p;
        bool ok = (p.getX() == 0.0 && p.getY() == 0.0);
        assertTest("TC01: Конструктор по умолчанию Point() инициализирует (0.0, 0.0)",
            ok, "(0.0; 0.0)", "(" + std::to_string(p.getX()) + "; " + std::to_string(p.getY()) + ")", passed, failed);
    }
    {
        Point p(3.5, -4.5);
        bool ok = (p.getX() == 3.5 && p.getY() == -4.5);
        assertTest("TC02: Конструктор Point(x, y) с вещественными координатами",
            ok, "(3.5; -4.5)", "(" + std::to_string(p.getX()) + "; " + std::to_string(p.getY()) + ")", passed, failed);
    }
    {
        Point p1(0.0, 0.0);
        Point p2(3.0, 4.0);
        double d = distance(p1, p2);
        bool ok = (std::fabs(d - 5.0) < 0.0001);
        assertTest("TC03: Функция distance для расстояния между (0,0) и (3,4)",
            ok, "5.0", std::to_string(d), passed, failed);
    }
    {
        Point p(2.0, 2.0);
        double d = distance(p, p);
        bool ok = (std::fabs(d - 0.0) < 0.0001);
        assertTest("TC04: Функция distance от точки до самой себя равна 0",
            ok, "0.0", std::to_string(d), passed, failed);
    }

    // [2] Тесты класса Square
    std::cout << "\n[2] Тесты класса Square: валидация, произвольный порядок точек, getArea, getPerimeter, getPoints\n";
    {
        Point p1(0.0, 0.0), p2(2.0, 0.0), p3(2.0, 2.0), p4(0.0, 2.0);
        Square sq(p1, p2, p3, p4);
        assertTest("TC05: Валидный стандартный квадрат 2x2 -> isValid() == true",
            sq.isValid() == true, "true", boolToString(sq.isValid()), passed, failed);
        assertTest("TC06: Сторона квадрата getSide() для стороны 2",
            std::fabs(sq.getSide() - 2.0) < 0.0001, "2.0", std::to_string(sq.getSide()), passed, failed);
        assertTest("TC07: Площадь квадрата getArea() для стороны 2",
            std::fabs(sq.getArea() - 4.0) < 0.0001, "4.0", std::to_string(sq.getArea()), passed, failed);
        assertTest("TC08: Периметр квадрата getPerimeter() для стороны 2",
            std::fabs(sq.getPerimeter() - 8.0) < 0.0001, "8.0", std::to_string(sq.getPerimeter()), passed, failed);
    }
    {
        // Перемешанный произвольный порядок вершин квадрата
        Point p1(2.0, 2.0), p2(0.0, 0.0), p3(0.0, 2.0), p4(2.0, 0.0);
        Square sq(p1, p2, p3, p4);
        bool ok = sq.isValid() && (std::fabs(sq.getArea() - 4.0) < 0.0001);
        assertTest("TC09: Создание Square при произвольном порядке передачи 4 точек",
            ok, "isValid=true, area=4.0", "isValid=" + boolToString(sq.isValid()) + ", area=" + std::to_string(sq.getArea()), passed, failed);
    }
    {
        // Повернутый квадрат под углом 45 градусов
        Point p1(1.0, 0.0), p2(2.0, 1.0), p3(1.0, 2.0), p4(0.0, 1.0);
        Square sq(p1, p2, p3, p4);
        bool ok = sq.isValid() && (std::fabs(sq.getArea() - 2.0) < 0.0001);
        assertTest("TC10: Повернутый квадрат под 45 градусов -> площадь равна 2.0",
            ok, "area=2.0", "area=" + std::to_string(sq.getArea()), passed, failed);
    }
    {
        // Проверка метода getPoints()
        Point p1(0.0, 0.0), p2(2.0, 0.0), p3(2.0, 2.0), p4(0.0, 2.0);
        Square sq(p1, p2, p3, p4);
        Point* pts = sq.getPoints();
        bool ok = (pts != nullptr && pts[0].getX() == 0.0 && pts[0].getY() == 0.0);
        assertTest("TC11: Метод getPoints() возвращает массив из 4 упорядоченных точек",
            ok, "указатель на 4 точки", (pts != nullptr ? "успешно получен" : "nullptr"), passed, failed);
    }
    {
        // Невалидный квадрат: 4 совпадающие точки
        Point p(1.0, 1.0);
        Square sq(p, p, p, p);
        assertTest("TC12: Вырожденный случай: совпадающие 4 точки -> isValid() == false",
            sq.isValid() == false, "false", boolToString(sq.isValid()), passed, failed);
    }
    {
        // Невалидный квадрат: 4 точки на одной прямой
        Point p1(0.0, 0.0), p2(1.0, 1.0), p3(2.0, 2.0), p4(3.0, 3.0);
        Square sq(p1, p2, p3, p4);
        assertTest("TC13: Коллинеарные 4 точки на прямой -> isValid() == false",
            sq.isValid() == false, "false", boolToString(sq.isValid()), passed, failed);
    }
    {
        // Невалидный квадрат: прямоугольник с неравными сторонами
        Point p1(0.0, 0.0), p2(4.0, 0.0), p3(4.0, 2.0), p4(0.0, 2.0);
        Square sq(p1, p2, p3, p4);
        assertTest("TC14: Прямоугольник (не квадрат) -> isValid() == false",
            sq.isValid() == false, "false", boolToString(sq.isValid()), passed, failed);
    }
    {
        // Невалидный квадрат: ромб с неравными диагоналями
        Point p1(0.0, 0.0), p2(2.0, 1.0), p3(4.0, 0.0), p4(2.0, -1.0);
        Square sq(p1, p2, p3, p4);
        assertTest("TC15: Ромб с неравными диагоналями -> isValid() == false",
            sq.isValid() == false, "false", boolToString(sq.isValid()), passed, failed);
    }

    // [3] Тесты функции L4: getParallelLines
    std::cout << "\n[3] Тесты функции L4: getParallelLines (нахождение двух параллельных линий)\n";
    {
        Point pts[4] = { Point(0.0, 0.0), Point(2.0, 0.0), Point(0.0, 3.0), Point(2.0, 3.0) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 4, p11, p12, p21, p22);
        assertTest("TC16: Горизонтальные параллельные линии -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Point pts[4] = { Point(1.0, 0.0), Point(1.0, 4.0), Point(5.0, 2.0), Point(5.0, 8.0) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 4, p11, p12, p21, p22);
        assertTest("TC17: Вертикальные параллельные линии -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Point pts[4] = { Point(0.0, 0.0), Point(2.0, 2.0), Point(1.0, 0.0), Point(3.0, 2.0) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 4, p11, p12, p21, p22);
        assertTest("TC18: Наклонные параллельные линии под 45 градусов -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        // Проверка устойчивости к точности double (погрешность округления 0.0001)
        Point pts[4] = { Point(0.0, 0.0), Point(0.1, 0.3), Point(1.0, 1.0), Point(1.3, 1.9) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 4, p11, p12, p21, p22);
        assertTest("TC19: Параллельные линии с дробными координатами (компенсация точности double) -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        // Нет параллельных линий
        Point pts[4] = { Point(0.0, 0.0), Point(3.0, 0.0), Point(2.0, 3.0), Point(0.0, 2.0) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 4, p11, p12, p21, p22);
        assertTest("TC20: Набор точек без параллельных линий -> false",
            res == false, "false", boolToString(res), passed, failed);
    }
    {
        // BVA: размер меньше 4 точек
        Point pts[3] = { Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0) };
        Point p11, p12, p21, p22;
        bool res = getParallelLines(pts, 3, p11, p12, p21, p22);
        assertTest("TC21: BVA: Массив из 3 точек (размер < 4) -> false",
            res == false, "false", boolToString(res), passed, failed);
    }
    {
        // BVA: нулевой указатель
        Point p11, p12, p21, p22;
        bool res = getParallelLines(nullptr, 4, p11, p12, p21, p22);
        assertTest("TC22: BVA: Указатель nullptr -> false",
            res == false, "false", boolToString(res), passed, failed);
    }

    // [4] Тесты функции P3: getClosestPoint
    std::cout << "\n[4] Тесты функции P3: getClosestPoint (точка с минимальной суммой расстояний)\n";
    {
        Point pts[3] = { Point(-2.0, 0.0), Point(0.0, 0.0), Point(2.0, 0.0) };
        Point closest = getClosestPoint(pts, 3);
        bool ok = (closest.getX() == 0.0 && closest.getY() == 0.0);
        assertTest("TC23: Симметричный отрезок [-2, 0, 2] -> центральная точка (0.0, 0.0)",
            ok, "(0.0; 0.0)", "(" + std::to_string(closest.getX()) + "; " + std::to_string(closest.getY()) + ")", passed, failed);
    }
    {
        Point pts[4] = { Point(0.0, 0.0), Point(6.0, 0.0), Point(3.0, 5.196), Point(3.0, 1.732) };
        Point closest = getClosestPoint(pts, 4);
        bool ok = (std::fabs(closest.getX() - 3.0) < 0.01 && std::fabs(closest.getY() - 1.732) < 0.01);
        assertTest("TC24: Вершины треугольника и центр -> центр с минимальной суммой расстояний",
            ok, "(3.0; 1.732)", "(" + std::to_string(closest.getX()) + "; " + std::to_string(closest.getY()) + ")", passed, failed);
    }
    {
        // BVA: размер 1
        Point single(7.0, 9.0);
        Point closest = getClosestPoint(&single, 1);
        bool ok = (closest.getX() == 7.0 && closest.getY() == 9.0);
        assertTest("TC25: BVA: Массив из 1 точки -> возвращается эта же точка",
            ok, "(7.0; 9.0)", "(" + std::to_string(closest.getX()) + "; " + std::to_string(closest.getY()) + ")", passed, failed);
    }
    {
        // BVA: nullptr
        Point closest = getClosestPoint(nullptr, 5);
        bool ok = (closest.getX() == 0.0 && closest.getY() == 0.0);
        assertTest("TC26: BVA: Указатель nullptr -> возвращается точка (0.0, 0.0)",
            ok, "(0.0; 0.0)", "(" + std::to_string(closest.getX()) + "; " + std::to_string(closest.getY()) + ")", passed, failed);
    }

    // [5] Тесты функции F4: checkFigureCrossing
    std::cout << "\n[5] Тесты функции F4: checkFigureCrossing (пересечение квадратов)\n";
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        Square s2(Point(1.0, 1.0), Point(3.0, 1.0), Point(3.0, 3.0), Point(1.0, 3.0));
        bool res = checkFigureCrossing(s1, s2);
        assertTest("TC27: Частично перекрывающиеся квадраты -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0));
        Square s2(Point(5.0, 5.0), Point(6.0, 5.0), Point(6.0, 6.0), Point(5.0, 6.0));
        bool res = checkFigureCrossing(s1, s2);
        assertTest("TC28: Непересекающиеся удаленные квадраты -> false",
            res == false, "false", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(10.0, 0.0), Point(10.0, 10.0), Point(0.0, 10.0));
        Square s2(Point(2.0, 2.0), Point(4.0, 2.0), Point(4.0, 4.0), Point(2.0, 4.0));
        bool res = checkFigureCrossing(s1, s2);
        assertTest("TC29: Квадрат s2 полностью внутри квадрата s1 -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        Square s2(Point(2.0, 0.0), Point(4.0, 0.0), Point(4.0, 2.0), Point(2.0, 2.0));
        bool res = checkFigureCrossing(s1, s2);
        assertTest("TC30: Квадраты соприкасаются по общей стороне -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        Square s2(Point(2.0, 2.0), Point(4.0, 2.0), Point(4.0, 4.0), Point(2.0, 4.0));
        bool res = checkFigureCrossing(s1, s2);
        assertTest("TC31: Квадраты соприкасаются в одной угловой точке -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        // Повернутый под 45 градусов квадрат с центром в (2, 1)
        Square sRot(Point(2.0, 0.0), Point(3.0, 1.0), Point(2.0, 2.0), Point(1.0, 1.0));
        bool res = checkFigureCrossing(s1, sRot);
        assertTest("TC32: Повернутый под 45 градусов квадрат пересекает обычный -> true",
            res == true, "true", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        Square sRot(Point(10.0, 10.0), Point(11.0, 11.0), Point(10.0, 12.0), Point(9.0, 11.0));
        bool res = checkFigureCrossing(s1, sRot);
        assertTest("TC33: Повернутый квадрат далеко от первого -> false",
            res == false, "false", boolToString(res), passed, failed);
    }
    {
        Square s1(Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0));
        Square sInv(Point(0.0, 0.0), Point(0.0, 0.0), Point(0.0, 0.0), Point(0.0, 0.0));
        bool res = checkFigureCrossing(s1, sInv);
        assertTest("TC34: Проверка с невалидной фигурой -> false",
            res == false, "false", boolToString(res), passed, failed);
    }

    // [6] Тесты управления динамической памятью
    std::cout << "\n[6] Тесты управления динамической памятью: freePointsArray\n";
    {
        Point* arr = new Point[4];
        freePointsArray(arr);
        assertTest("TC35: freePointsArray освобождает память и обнуляет указатель в nullptr",
            arr == nullptr, "nullptr", (arr == nullptr ? "nullptr" : "не nullptr"), passed, failed);
    }
    {
        Point* arr = nullptr;
        freePointsArray(arr);
        assertTest("TC36: freePointsArray безопасно обрабатывает nullptr без сбоя",
            arr == nullptr, "nullptr", (arr == nullptr ? "nullptr" : "не nullptr"), passed, failed);
    }

    std::cout << "\nИтоги тестирования:\n";
    std::cout << "  Всего тестов: " << (passed + failed) << "\n";
    std::cout << "  Пройдено:     " << passed << "\n";
    std::cout << "  Провалено:    " << failed << "\n";
}
