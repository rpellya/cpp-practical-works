// Практическая работа 3. Фигуры и точки
// Вариант 6 (c1 = 'P', c2 = 'R')
// Формула: V = (10 * int(c1) + int(c2)) % 12 = 882 % 12 = 6
// Типы данных: Point, Square
// Вычислительные функции: L4, P3, F4

#include <iostream>
#include <windows.h>
#include <string>
#include "Point.h"
#include "Square.h"
#include "geometry_functions.h"
#include "tests.h"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    const char c1 = 'P';
    const char c2 = 'R';
    const int variant = (10 * int(c1) + int(c2)) % 12;

    std::cout << "Практическая работа 3. Фигуры и точки\n";
    std::cout << "Расчет варианта:\n";
    std::cout << "  c1 = '" << c1 << "' (ASCII: " << int(c1) << ")\n";
    std::cout << "  c2 = '" << c2 << "' (ASCII: " << int(c2) << ")\n";
    std::cout << "  V = (10 * " << int(c1) << " + " << int(c2) << ") % 12 = 882 % 12 = " << variant << "\n";
    std::cout << "  Типы данных: Point, Square\n";
    std::cout << "  Функции: L4, P3, F4\n\n";

    Point* userPoints = nullptr;
    int userPointsCount = 0;

    Square square1;
    Square square2;
    bool hasSquare1 = false;
    bool hasSquare2 = false;

    bool exitFlag = false;
    char choice = ' ';

    while (!exitFlag) {
        std::cout << "\nМеню:\n";
        std::cout << " 1 - Исследование фигуры Квадрат (создание Square по 4 точкам, getArea, getPerimeter, getPoints)\n";
        std::cout << " 2 - Ввести массив точек для функций L4 и P3\n";
        std::cout << " 3 - Вычислить L4: Нахождение двух пар точек, определяющих параллельные линии\n";
        std::cout << " 4 - Вычислить P3: Нахождение точки с минимальной суммой расстояний до остальных\n";
        std::cout << " 5 - Вычислить F4: Проверка пересечения двух фигур Square\n";
        std::cout << " 6 - Вывести текущие сохраненные данные (массив точек и фигуры)\n";
        std::cout << " 7 - Очистить сохраненные данные (сброс памяти)\n";
        std::cout << " t - Запуск EP-тестов (Equivalence Partitioning & BVA)\n";
        std::cout << " q, e - Выход из программы\n";
        std::cout << "\nВыберите пункт меню: ";

        if (!(std::cin >> choice)) {
            break;
        }

        while ((unsigned char)choice > 127) {
            if (!(std::cin >> choice)) {
                exitFlag = true;
                break;
            }
        }
        if (exitFlag) break;

        std::cin.ignore(256, '\n');

        switch (choice) {
            case '1': {
                std::cout << "\nПункт 1: Создание и исследование фигуры Square\n";
                Square sq = inputSquare("Квадрат №1");

                if (sq.isValid()) {
                    square1 = sq;
                    hasSquare1 = true;
                    std::cout << "\nИнформация о фигуре (print):\n";
                    sq.print();

                    // Демонстрация прямого вызова всех методов из задания
                    std::cout << "\nДемонстрация работы методов класса Square:\n";
                    std::cout << "  sq.getSide(): " << sq.getSide() << "\n";
                    std::cout << "  sq.getPerimeter(): " << sq.getPerimeter() << "\n";
                    std::cout << "  sq.getArea(): " << sq.getArea() << "\n";
                    std::cout << "  sq.getPoints() (массив из 4 точек):\n";
                    Point* pts = sq.getPoints();
                    for (int i = 0; i < 4; ++i) {
                        std::cout << "    [" << i << "] ";
                        pts[i].print();
                        std::cout << "\n";
                    }
                } else {
                    std::cout << "Внимание: введенные точки не образуют валидный квадрат. Фигура не сохранена.\n";
                }
                break;
            }

            case '2': {
                std::cout << "\nПункт 2: Ввод массива точек для функций L4 и P3\n";
                int newCount = 0;
                Point* newPoints = inputPointsArray(newCount);

                // Заменяем старые данные только после успешного ввода новых
                if (newPoints != nullptr && newCount > 0) {
                    if (userPoints != nullptr) {
                        std::cout << "Предыдущий массив точек заменен новым.\n";
                        freePointsArray(userPoints);
                    }
                    userPoints = newPoints;
                    userPointsCount = newCount;
                    std::cout << "Массив из " << userPointsCount << " точек успешно сохранен!\n";
                    printPointsArray(userPoints, userPointsCount, "userPoints");
                } else {
                    std::cout << "Ввод массива не выполнен или отменен. Предыдущие данные сохранены без изменений.\n";
                }
                break;
            }

            case '3': {
                std::cout << "\nПункт 3: Вычисление функции L4 (getParallelLines)\n";

                if (userPoints == nullptr || userPointsCount < 4) {
                    std::cout << "Внимание: для работы функции L4 требуется массив минимум из 4 точек!\n";
                    std::cout << "Текущий массив содержит: " << userPointsCount << " точек.\n";
                    std::cout << "Желаете ввести массив сейчас? (1 - да, 0 - отмена): ";
                    int ans = readInt("", 0, 1);
                    if (ans == 1) {
                        int newCount = 0;
                        Point* newPoints = inputPointsArray(newCount);
                        // Заменяем массив только при успешном вводе
                        if (newPoints != nullptr && newCount > 0) {
                            freePointsArray(userPoints);
                            userPoints = newPoints;
                            userPointsCount = newCount;
                        } else {
                            std::cout << "Ввод массива отменен. Предыдущие данные сохранены.\n";
                        }
                    } else {
                        break;
                    }
                }

                if (userPoints == nullptr || userPointsCount < 4) {
                    std::cout << "Ошибка: недостаточно точек для проверки L4.\n";
                    break;
                }

                Point p11, p12, p21, p22;
                bool found = getParallelLines(userPoints, userPointsCount, p11, p12, p21, p22);
                if (found) {
                    std::cout << "\nРезультат L4: найдены две пары точек, задающие параллельные линии:\n";
                    std::cout << "  Линия 1 (p11, p12): ";
                    p11.print();
                    std::cout << " и ";
                    p12.print();
                    std::cout << "\n  Линия 2 (p21, p22): ";
                    p21.print();
                    std::cout << " и ";
                    p22.print();
                    std::cout << "\n";
                } else {
                    std::cout << "\nРезультат L4: среди заданных точек не найдено параллельных линий.\n";
                }
                break;
            }

            case '4': {
                std::cout << "\nПункт 4: Вычисление функции P3 (getClosestPoint)\n";

                if (userPoints == nullptr || userPointsCount <= 0) {
                    std::cout << "Внимание: массив точек пуст.\n";
                    std::cout << "Желаете ввести массив сейчас? (1 - да, 0 - отмена): ";
                    int ans = readInt("", 0, 1);
                    if (ans == 1) {
                        int newCount = 0;
                        Point* newPoints = inputPointsArray(newCount);
                        // Заменяем массив только при успешном вводе
                        if (newPoints != nullptr && newCount > 0) {
                            freePointsArray(userPoints);
                            userPoints = newPoints;
                            userPointsCount = newCount;
                        } else {
                            std::cout << "Ввод массива отменен. Предыдущие данные сохранены.\n";
                        }
                    } else {
                        break;
                    }
                }

                if (userPoints == nullptr || userPointsCount <= 0) {
                    std::cout << "Ошибка: массив точек не задан.\n";
                    break;
                }

                Point closest = getClosestPoint(userPoints, userPointsCount);
                std::cout << "\nРезультат P3: точка с минимальной суммой расстояний: ";
                closest.print();
                std::cout << "\n";
                break;
            }

            case '5': {
                std::cout << "\nПункт 5: Вычисление функции F4 (checkFigureCrossing)\n";

                // Если оба квадрата уже были заданы, предлагаем выбор
                if (hasSquare1 && hasSquare2) {
                    std::cout << "В памяти найдены ранее заданные квадраты №1 и №2.\n";
                    std::cout << "Использовать сохраненные квадраты (1) или ввести новые (2)?: ";
                    int choiceSquares = readInt("", 1, 2);
                    if (choiceSquares == 2) {
                        Square s1 = inputSquare("Квадрат №1");
                        Square s2 = inputSquare("Квадрат №2");
                        if (s1.isValid() && s2.isValid()) {
                            square1 = s1;
                            square2 = s2;
                            hasSquare1 = true;
                            hasSquare2 = true;
                        } else {
                            std::cout << "Один или оба квадрата невалидны. Проверка отменена, сохранены прежние фигуры.\n";
                            break;
                        }
                    }
                } else {
                    Square s1 = inputSquare("Квадрат №1");
                    Square s2 = inputSquare("Квадрат №2");
                    if (s1.isValid() && s2.isValid()) {
                        square1 = s1;
                        square2 = s2;
                        hasSquare1 = true;
                        hasSquare2 = true;
                    } else {
                        std::cout << "\nОшибка: один или оба квадрата не являются валидными!\n";
                        break;
                    }
                }

                std::cout << "\nПервый квадрат:\n";
                square1.print();
                std::cout << "\nВторой квадрат:\n";
                square2.print();

                bool crossing = checkFigureCrossing(square1, square2);
                if (crossing) {
                    std::cout << "\nРезультат F4: квадраты ПЕРЕСЕКАЮТСЯ (имеют общие точки).\n";
                } else {
                    std::cout << "\nРезультат F4: квадраты НЕ пересекаются.\n";
                }
                break;
            }

            case '6': {
                std::cout << "\nПункт 6: Текущие сохраненные данные\n";
                printPointsArray(userPoints, userPointsCount, "userPoints");

                std::cout << "\nКвадрат №1:\n";
                if (hasSquare1) {
                    square1.print();
                } else {
                    std::cout << "  Не задан.\n";
                }

                std::cout << "\nКвадрат №2:\n";
                if (hasSquare2) {
                    square2.print();
                } else {
                    std::cout << "  Не задан.\n";
                }
                break;
            }

            case '7': {
                std::cout << "\nПункт 7: Очистка сохраненных данных\n";
                freePointsArray(userPoints);
                userPointsCount = 0;
                hasSquare1 = false;
                hasSquare2 = false;
                std::cout << "Память очищена, указатели сброшены в nullptr.\n";
                break;
            }

            case 't': {
                runEquivalencePartitioningTests();
                break;
            }

            case 'q':
            case 'e': {
                std::cout << "\nВыход из программы. Освобождение ресурсов...\n";
                freePointsArray(userPoints);
                userPointsCount = 0;
                std::cout << "Память освобождена. До свидания!\n";
                exitFlag = true;
                break;
            }

            default: {
                std::cout << "Неизвестный пункт меню. Попробуйте снова.\n";
                break;
            }
        }
    }

    // Гарантированное освобождение динамической памяти при любом выходе
    freePointsArray(userPoints);
    userPointsCount = 0;

    return 0;
}
