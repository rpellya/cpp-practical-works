// Практическая работа 2. Работа с динамическими массивами и указателями в C++ 
// Вариант 0 (P): Матричное умножение

// Файл: source.cpp (Консольное меню, управление жизненным циклом памяти, интерактивное взаимодействие с пользователем и EP-тесты)

#include <iostream>
#include <windows.h>
#include <climits>
#include <clocale>
#include <string>
#include "matrix.h"

using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    const char mySecondName = 'P'; // Pellya. P = 80
    const int myVariant = int(mySecondName) % 8; // 0. 80 % 8 = 0

    cout << "Практическая работа номер 2: Работа с динамическими массивами и указателями в C++" << endl;
    cout << "Расчет варианта: V = int('" << mySecondName << "') % 8 = " << int(mySecondName) << " % 8 = " << myVariant << endl;
    cout << "Операция по варианту 0: Матричное умножение" << endl;

    // Динамическая матрица A
    int** matrixA = nullptr;
    int rowsA = 0;
    int colsA = 0;

    // матрица B
    int** matrixB = nullptr;
    int rowsB = 0;
    int colsB = 0;

    // результат-матрица C 
    int** matrixC = nullptr;
    int rowsC = 0;
    int colsC = 0;

    // вектор V
    int* vectorV = nullptr;
    int sizeV = 0;

    bool exitFlag = false;
    char inputUser;

    while (!exitFlag) {
        cout << "\nМеню\n";
        cout << " 1 - Задать матрицу A (размеры и элементы)\n";
        cout << " 2 - Задать матрицу B (размеры и элементы)\n";
        cout << " 3 - Вывести текущие матрицы на консоль (A, B, C)\n";
        cout << " 4 - Вычислить матричное умножение: C = A * B\n";
        cout << " 5 - Задать динамический вектор\n";
        cout << " 6 - Вывести динамический вектор на консоль\n";
        cout << " 7 - Очистить всю выделенную память (сброс данных)\n";
        cout << " t - Запуск EP-тестов\n";
        cout << " q, e - Выход из программы\n";
        cout << "\nВыберите пункт меню: ";

        cin >> inputUser;
        if (cin.fail()) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Некорректный ввод. Повторите попытку.\n";
            continue;
        }
        cin.ignore(256, '\n');

        switch (inputUser)
        {
            case '1':
            {
                // Если матрица A уже существовала - освобождаем память
                if (matrixA != nullptr) {
                    cout << "Текущая матрица A будет заменена новой.\n";
                    freeMatrix(matrixA, rowsA);
                }
            
                // Если был ранее вычислен результат C, он становится неактуальным
                if (matrixC != nullptr) {
                    freeMatrix(matrixC, rowsC);
                    rowsC = colsC = 0;
                }

                inputMatrixDimensions(rowsA, colsA, "A");
                matrixA = allocateMatrix(rowsA, colsA);
                inputMatrixElements(matrixA, rowsA, colsA, "A");
                break;
            }

            case '2':
            {
                // Если матрица B уже существовала - освобождаем память
                if (matrixB != nullptr) {
                    cout << "Текущая матрица B будет заменена новой.\n";
                    freeMatrix(matrixB, rowsB);
                }

                // Если был ранее вычислен результат C, он становится неактуальным
                if (matrixC != nullptr) {
                    freeMatrix(matrixC, rowsC);
                    rowsC = colsC = 0;
                }

                inputMatrixDimensions(rowsB, colsB, "B");
                matrixB = allocateMatrix(rowsB, colsB);
                inputMatrixElements(matrixB, rowsB, colsB, "B");
                break;
            }

            case '3':
            {
                cout << "\nВывод текущих матриц\n";
                printMatrix(matrixA, rowsA, colsA, "A");
                printMatrix(matrixB, rowsB, colsB, "B");

                if (matrixC != nullptr) {
                    printMatrix(matrixC, rowsC, colsC, "C (Результат A * B)");
                }

                else {
                    cout << "Матрица C (результат произведения) пока не вычислена.\n";
                }
                break;
            }

            case '4':
            {
                cout << "\nВычисление: Матричное Умножение C = A * B\n";
                if (matrixA == nullptr) {
                    cout << "Ошибка: Матрица A не задана! Сначала выберите пункт 1.\n";
                    break;
                }
                
                if (matrixB == nullptr) {
                    cout << "Ошибка: Матрица B не задана! Сначала выберите пункт 2.\n";
                    break;
                }

                cout << "Размеры матрицы A: " << rowsA << "x" << colsA << endl;
                cout << "Размеры матрицы B: " << rowsB << "x" << colsB << endl;

                if (!canMultiply(colsA, rowsB)) {
                    cout << "Ошибка: Умножение невозможно!\n";
                    cout << "Условие совместимости (colsA == rowsB) нарушено: " << colsA << " != " << rowsB << ".\n";
                    cout << "Число столбцов первой матрицы должно совпадать с числом строк второй.\n";
                    break;
                }

                // освобождаем старый результат, если он был
                if (matrixC != nullptr) {
                    freeMatrix(matrixC, rowsC);
                }

                matrixC = multiplyMatrices(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
                rowsC = rowsA;
                colsC = colsB;

                cout << "Произведение успешно вычислено! Размер результирующей матрицы C: " << rowsC << "x" << colsC << endl;
                printMatrix(matrixC, rowsC, colsC, "C (A * B)");
                break;
            }

            case '5':
            {
                inputVector(vectorV, sizeV, "V");
                break;
            }

            case '6':
            {
                printVector(vectorV, sizeV, "V");
                break;
            }

            case '7':
            {
                cout << "\nОсвобождение всей выделенной динамической памяти...\n";
                freeMatrix(matrixA, rowsA);
                rowsA = colsA = 0;

                freeMatrix(matrixB, rowsB);
                rowsB = colsB = 0;

                freeMatrix(matrixC, rowsC);
                rowsC = colsC = 0;

                freeVector(vectorV);
                sizeV = 0;

                cout << "Память успешно очищена! Все указатели занулены (nullptr).\n";
                break;
            }

            case 't':
            {
                runEquivalencePartitioningTests();
                break;
            }

            case 'q':
            case 'e':
            {
                cout << "\nЗавершение программы! Освобождение всех выделенных ресурсов...\n";
                freeMatrix(matrixA, rowsA);
                freeMatrix(matrixB, rowsB);
                freeMatrix(matrixC, rowsC);
                freeVector(vectorV);

                cout << "Все ресурсы освобождены! До свидания!\n";
                
                exitFlag = true;
                break;
            }

            default:
            {
                cout << "Увы! Такого пункта меню нет. Попробуйте снова.\n";
                break;
            }
        }
    }
    return 0;
}