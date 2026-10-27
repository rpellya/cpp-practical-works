#include "matrix.h"

using namespace std;

// Выделение памяти под двумерный динамический массив
// Сначала выделяется массив указателей на строки (int* [rows]),
// а затем для каждой строки выделяется блок памяти под столбцы (new int[cols]).
int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols](); // инициализация нулями
    }

    return matrix;
}

// Освобождение динамической памяти двумерного массива.
// Сделал как в лекции: сначала удаляем каждую строку, затем массив указателей
// затем зануляем указатель через nullptr
void freeMatrix(int**& matrix, int rows) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

// Выделение памяти под одномерный динамический массив
int* allocateVector(int size) {
    if (size <= 0) {
        return nullptr;
    }
    return new int[size]();
}

// Освобождение памяти одномерного динамического массива
void freeVector(int*& vec) {
    if (vec != nullptr) {
        delete[] vec;
        vec = nullptr;
    }
}

// Глубокое копирование матрицы в новую область динамической памяти
int** copyMatrix(int** src, int rows, int cols) {
    if (src == nullptr || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** dst = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            dst[i][j] = src[i][j];
        }
    }

    return dst;
}

// Проверка равенства элементов двух матриц
bool areMatricesEqual(int** a, int** b, int rows, int cols) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    if (rows <= 0 || cols <= 0) return false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Безопасный ввод целого числа с консоли с обработкой ошибок
int readInt(const string& input, int minValue, int maxValue) {
    int value;
    
    while (true) {
        cout << input;
        
        if (cin >> value) {
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            
            cout << "Ошибка: число должно быть в диапазоне от " << minValue << " до " << maxValue << ". Повторите ввод.\n";
        }
        
        else {
            if (cin.eof()) {
                return minValue;
            }
            cin.clear();
            cin.ignore(256, '\n');
            
            cout << "Некорректный ввод: ожидается целое число. Повторите ввод.\n";
        }
    }
}

// Запрос и валидация размеров матрицы
void inputMatrixDimensions(int& rows, int& cols, const string& matrixName) {
    cout << "\nЗадание размеров матрицы " << matrixName << endl;
    
    rows = readInt("Введите количество строк (от 1 до 50): ", 1, 50);
    cols = readInt("Введите количество столбцов (от 1 до 50): ", 1, 50);
}

// Поэлементный ввод элементов матрицы
void inputMatrixElements(int** matrix, int rows, int cols, const string& matrixName) {
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
        cout << "Ошибка: матрица не выделена в памяти!\n";
        return;
    }

    cout << "\nВведите элементы матрицы " << matrixName << " (" << rows << "x" << cols << "):\n";
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            string input = "  Элемент [" + to_string(i) + "][" + to_string(j) + "]: ";
            matrix[i][j] = readInt(input, -1000000, 1000000);
        }
    }
    
    cout << "Матрица " << matrixName << " успешно заполнена.\n";
}

// Ввод динамического одномерного вектора
void inputVector(int*& vec, int& size, const string& vectorName) {
    cout << "\nЗадание размера вектора " << vectorName << endl;
    
    int newSize = readInt("Введите размер вектора (от 1 до 100): ", 1, 100);

    // Если вектор уже был выделен - освобождаем старую память
    freeVector(vec);
    size = newSize;
    vec = allocateVector(size);

    cout << "\nВведите элементы вектора " << vectorName << " (размер " << size << "):\n";
    
    for (int i = 0; i < size; ++i) {
        string input = "  Элемент [" + to_string(i) + "]: ";
        vec[i] = readInt(input, -1000000, 1000000);
    }
    
    cout << "Вектор " << vectorName << " успешно заполнен.\n";
}

void inputVectorElements(int* vec, int size, const string& vectorName) {
    if (vec == nullptr || size <= 0) {
        cout << "Ошибка: вектор не инициализирован.\n";
        return;
    }
    
    cout << "\nВведите элементы вектора " << vectorName << " (размер " << size << "):\n";
    
    for (int i = 0; i < size; ++i) {
        string input = "  Элемент [" + std::to_string(i) + "]: ";
        vec[i] = readInt(input, -1000000, 1000000);
    }
}

// вывод матрицы с использованием указателей и адресной арифметики
void printMatrix(int** matrix, int rows, int cols, const string& matrixName) {
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
        cout << "Матрица " << matrixName << " пуста или не инициализирована.\n";
        return;
    }

    cout << "\nМатрица " << matrixName << " (" << rows << "x" << cols << ") =" << endl;

    int** const rowEnd = matrix + rows;
    for (int** rowPtr = matrix; rowPtr < rowEnd; ++rowPtr) {
        int* const colEnd = *rowPtr + cols;
        
        for (int* colPtr = *rowPtr; colPtr < colEnd; ++colPtr) {
            cout << *colPtr << "\t";
        }
        cout << endl;
    }
}

void printVector(const int* vec, int size, const string& vectorName) {
    if (vec == nullptr || size <= 0) {
        cout << "Вектор " << vectorName << " пуст или не инициализирован.\n";
        return;
    }

    cout << "\nВектор " << vectorName << " (размер " << size << ") \n[ ";

    // Доступ через указатели и адресную арифметику
    const int* const endPtr = vec + size;
    for (const int* ptr = vec; ptr < endPtr; ++ptr) {
        cout << *ptr;

        if (ptr + 1 < endPtr) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

// Проверка критерия совместимости матриц при умножении:
// Матрицы A (m x k) и B (k x n) можно перемножить тогда и только тогда,
// когда число столбцов первой матрицы равно числу строк второй (colsA == rowsB).
bool canMultiply(int colsA, int rowsB) {
    return (colsA > 0 && rowsB > 0 && colsA == rowsB);
}

// Вычисление матричного произведения: C = A * B
// Результирующая матрица C имеет размерность rowsA x colsB.
int** multiplyMatrices(int** a, int rowsA, int colsA, int** b, int rowsB, int colsB) {
    if (a == nullptr || b == nullptr) {
        return nullptr;
    }

    // Проверка корректности размеров и условия совместимости
    if (rowsA <= 0 || colsA <= 0 || rowsB <= 0 || colsB <= 0) {
        return nullptr;
    }

    if (colsA != rowsB) {
        return nullptr;
    }

    // Выделение памяти под результирующую матрицу rowsA * colsB
    int** c = allocateMatrix(rowsA, colsB);
    if (c == nullptr) {
        return nullptr;
    }

    // Алгоритм матричного умножения: C[i][j] = sum(A[i][p] * B[p][j])
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int sum = 0;
            
            for (int p = 0; p < colsA; ++p) {
                sum += a[i][p] * b[p][j];
            }
            
            c[i][j] = sum;
        }
    }

    return c;
}
