// Equivalence Partitioning & Boundary Value Analysis

#include <iostream>
#include <sstream>
#include <string>
#include <climits>
#include "matrix.h"

using namespace std;

static void assertTest(const string& testName, bool condition, const string& details, int& passed, int& failed) {
    if (condition) {
        cout << "  [PASS] " << testName << endl;
        passed++;
    }
    else {
        cout << "  [FAIL] " << testName;
        if (!details.empty()) {
            cout << " -> " << details;
        }
        cout << endl;
        failed++;
    }
}

// Создание матрицы rows x cols и заполнение её данными (построчно)
static int** makeMatrix(int rows, int cols, const int* data) {
    int** m = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            m[i][j] = data[i * cols + j];
    return m;
}

// Вызов readInt с "вводом пользователя" из строки.
// На время вызова cin читает из строки, а cout пишет в строку (приглашения и ошибки).
// В result кладётся результат readInt, возвращается весь текст, выведенный функцией.
static string runReadInt(const string& input, int minV, int maxV, int& result) {
    istringstream in(input);
    ostringstream out;
    streambuf* oldIn = cin.rdbuf(in.rdbuf());
    streambuf* oldOut = cout.rdbuf(out.rdbuf());

    result = readInt("> ", minV, maxV);

    cout.rdbuf(oldOut);
    cin.rdbuf(oldIn);
    cin.clear();
    return out.str();
}

// Перехват вывода printMatrix
static string captureMatrix(int** m, int rows, int cols) {
    ostringstream out;
    streambuf* oldOut = cout.rdbuf(out.rdbuf());
    printMatrix(m, rows, cols, "T");
    cout.rdbuf(oldOut);
    return out.str();
}

// Перехват вывода printVector
static string captureVector(const int* v, int size) {
    ostringstream out;
    streambuf* oldOut = cout.rdbuf(out.rdbuf());
    printVector(v, size, "V");
    cout.rdbuf(oldOut);
    return out.str();
}

// Тесты
void runEquivalencePartitioningTests() {
    int passed = 0;
    int failed = 0;

    cout << "\nЗапуск Equivalence Partitioning & BVA тестов" << endl;

    cout << "\n[1] Тесты: allocateMatrix(rows, cols) " << endl;
    {
        int** m = allocateMatrix(3, 4);
        bool notNull = (m != nullptr);
        bool allZero = notNull;
        for (int i = 0; notNull && i < 3; ++i)
            for (int j = 0; j < 4; ++j)
                if (m[i][j] != 0) allZero = false;
        assertTest("TC1: Валидные размеры (3x4) -> не nullptr", notNull, "Ожидался не nullptr", passed, failed);
        assertTest("TC2: Валидные размеры (3x4) -> все элементы = 0", allZero, "Ожидалась инициализация нулями", passed, failed);
        freeMatrix(m, 3);
    }
    {
        int** m = allocateMatrix(1, 1);
        assertTest("TC3: BVA min: 1x1 -> не nullptr", m != nullptr && m[0][0] == 0, "Ожидалась матрица 1x1 из нуля", passed, failed);
        freeMatrix(m, 1);
    }
    {
        int** m = allocateMatrix(50, 50);
        bool ok = (m != nullptr);
        if (ok) { m[49][49] = 7; ok = (m[49][49] == 7 && m[0][0] == 0); }
        assertTest("TC4: BVA max меню: 50x50 -> доступен последний элемент", ok, "Ожидалась рабочая матрица 50x50", passed, failed);
        freeMatrix(m, 50);
    }
    
    assertTest("TC5: rows = 0 -> nullptr", allocateMatrix(0, 5) == nullptr, "Ожидался nullptr", passed, failed);
    assertTest("TC6: rows = -1 -> nullptr", allocateMatrix(-1, 5) == nullptr, "Ожидался nullptr", passed, failed);
    assertTest("TC7: cols = 0 -> nullptr", allocateMatrix(5, 0) == nullptr, "Ожидался nullptr", passed, failed);
    assertTest("TC8: cols = -1 -> nullptr", allocateMatrix(5, -1) == nullptr, "Ожидался nullptr", passed, failed);

    cout << "\n[2] Тесты: freeMatrix(matrix, rows) " << endl;
    {
        int** m = allocateMatrix(2, 2);
        freeMatrix(m, 2);
        assertTest("TC9: После освобождения указатель = nullptr", m == nullptr, "Ожидался nullptr", passed, failed);
    }
    {
        int** m = nullptr;
        freeMatrix(m, 3);
        assertTest("TC10: Освобождение nullptr безопасно (нет падения)", m == nullptr, "Ожидался nullptr", passed, failed);
    }
    {
        int** m = allocateMatrix(2, 2);
        freeMatrix(m, 2);
        freeMatrix(m, 2); // повторное освобождение
        assertTest("TC11: Двойное освобождение безопасно", m == nullptr, "Ожидался nullptr", passed, failed);
    }

    cout << "\n[3] Тесты: allocateVector(size) / freeVector(vec)" << endl;
    
    {
        int* v = allocateVector(5);
        bool ok = (v != nullptr);
        for (int i = 0; ok && i < 5; ++i)
            if (v[i] != 0) ok = false;
        assertTest("TC12: size = 5 -> не nullptr, все элементы = 0", ok, "Ожидался нулевой вектор", passed, failed);
        freeVector(v);
        assertTest("TC13: freeVector обнуляет указатель", v == nullptr, "Ожидался nullptr", passed, failed);
    }
    {
        int* v = allocateVector(1);
        assertTest("TC14: BVA min: size = 1 -> не nullptr", v != nullptr && v[0] == 0, "Ожидался вектор из 1 элемента", passed, failed);
        freeVector(v);
    }
    
    assertTest("TC15: BVA: size = 0 -> nullptr", allocateVector(0) == nullptr, "Ожидался nullptr", passed, failed);
    assertTest("TC16: size = -5 -> nullptr", allocateVector(-5) == nullptr, "Ожидался nullptr", passed, failed);
    
    {
        int* v = nullptr;
        freeVector(v);
        assertTest("TC17: freeVector(nullptr) безопасно", v == nullptr, "Ожидался nullptr", passed, failed);
    }

    cout << "\n[4] Тесты: copyMatrix(src, rows, cols)" << endl;
    
{
        const int d[] = { 1, 2, 3, 4, 5, 6 };
        int** src = makeMatrix(2, 3, d);
        int** cpy = copyMatrix(src, 2, 3);

        assertTest("TC18: Копия не nullptr и содержит те же значения", cpy != nullptr && areMatricesEqual(src, cpy, 2, 3), "Ожидалась равная копия", passed, failed);
        assertTest("TC19: Глубокое копирование: адреса строк различны", cpy != nullptr && src[0] != cpy[0] && src[1] != cpy[1], "Ожидались разные блоки памяти", passed, failed);

        if (cpy != nullptr) cpy[0][0] = 999;
        assertTest("TC20: Изменение копии не влияет на оригинал", src[0][0] == 1, "Оригинал изменился", passed, failed);

        freeMatrix(src, 2);
        freeMatrix(cpy, 2);
    }
    {
        const int d[] = { -7 };
        int** src = makeMatrix(1, 1, d);
        int** cpy = copyMatrix(src, 1, 1);
        assertTest("TC21: BVA: матрица 1x1 (отрицательное значение)", cpy != nullptr && cpy[0][0] == -7, "Ожидалось -7", passed, failed);
        freeMatrix(src, 1);
        freeMatrix(cpy, 1);
    }
    
    assertTest("TC22: src = nullptr -> nullptr", copyMatrix(nullptr, 2, 2) == nullptr, "Ожидался nullptr", passed, failed);
    
    {
        int** src = allocateMatrix(2, 2);
        assertTest("TC23: rows = 0 -> nullptr", copyMatrix(src, 0, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC24: cols = 0 -> nullptr", copyMatrix(src, 2, 0) == nullptr, "Ожидался nullptr", passed, failed);
        freeMatrix(src, 2);
    }

    cout << "\n[5] Тесты: areMatricesEqual(a, b, rows, cols) " << endl;
    {
        const int d1[] = { 1, 2, 3, 4 };
        const int d2[] = { 1, 2, 3, 4 };
        const int d3[] = { 9, 2, 3, 4 };
        const int d4[] = { 1, 2, 3, 9 };
        int** a = makeMatrix(2, 2, d1);
        int** b = makeMatrix(2, 2, d2);
        int** c = makeMatrix(2, 2, d3);
        int** d = makeMatrix(2, 2, d4);

        assertTest("TC25: Одинаковые матрицы -> true", areMatricesEqual(a, b, 2, 2) == true, "Ожидалось true", passed, failed);
        assertTest("TC26: Сравнение матрицы с самой собой -> true", areMatricesEqual(a, a, 2, 2) == true, "Ожидалось true", passed, failed);
        assertTest("TC27: BVA: отличается первый элемент [0][0] -> false", areMatricesEqual(a, c, 2, 2) == false, "Ожидалось false", passed, failed);
        assertTest("TC28: BVA: отличается последний элемент [1][1] -> false", areMatricesEqual(a, d, 2, 2) == false, "Ожидалось false", passed, failed);
        assertTest("TC29: Одна из матриц nullptr (a) -> false", areMatricesEqual(nullptr, b, 2, 2) == false, "Ожидалось false", passed, failed);
        assertTest("TC30: Одна из матриц nullptr (b) -> false", areMatricesEqual(a, nullptr, 2, 2) == false, "Ожидалось false", passed, failed);
        assertTest("TC31: Обе матрицы nullptr -> true", areMatricesEqual(nullptr, nullptr, 2, 2) == true, "Ожидалось true", passed, failed);
        assertTest("TC32: rows = 0 -> false", areMatricesEqual(a, b, 0, 2) == false, "Ожидалось false", passed, failed);
        assertTest("TC33: cols = 0 -> false", areMatricesEqual(a, b, 2, 0) == false, "Ожидалось false", passed, failed);

        freeMatrix(a, 2);
        freeMatrix(b, 2);
        freeMatrix(c, 2);
        freeMatrix(d, 2);
    }

    cout << "\n[6] Тесты: canMultiply(colsA, rowsB)" << endl;
    assertTest("TC34: Совместимы (3, 3) -> true", canMultiply(3, 3) == true, "Ожидалось true", passed, failed);
    assertTest("TC35: BVA min: (1, 1) -> true", canMultiply(1, 1) == true, "Ожидалось true", passed, failed);
    assertTest("TC36: BVA max меню: (50, 50) -> true", canMultiply(50, 50) == true, "Ожидалось true", passed, failed);
    assertTest("TC37: colsA < rowsB (2, 3) -> false", canMultiply(2, 3) == false, "Ожидалось false", passed, failed);
    assertTest("TC38: colsA > rowsB (3, 2) -> false", canMultiply(3, 2) == false, "Ожидалось false", passed, failed);
    assertTest("TC39: BVA: (0, 0) -> false", canMultiply(0, 0) == false, "Ожидалось false", passed, failed);
    assertTest("TC40: (0, 3) -> false", canMultiply(0, 3) == false, "Ожидалось false", passed, failed);
    assertTest("TC41: (3, 0) -> false", canMultiply(3, 0) == false, "Ожидалось false", passed, failed);
    assertTest("TC42: Отрицательные (-2, -2) -> false", canMultiply(-2, -2) == false, "Ожидалось false", passed, failed);

    cout << "\n[7] Тесты: multiplyMatrices(a, rowsA, colsA, b, rowsB, colsB)" << endl;
    {
        // 2x3 * 3x2 -> 2x2
        const int da[] = { 1, 2, 3, 4, 5, 6 };
        const int db[] = { 7, 8, 9, 10, 11, 12 };
        const int de[] = { 58, 64, 139, 154 };
        int** a = makeMatrix(2, 3, da);
        int** b = makeMatrix(3, 2, db);
        int** expected = makeMatrix(2, 2, de);
        int** c = multiplyMatrices(a, 2, 3, b, 3, 2);
        assertTest("TC43: Типовой случай 2x3 * 3x2 = [[58,64],[139,154]]", c != nullptr && areMatricesEqual(c, expected, 2, 2), "Неверное произведение", passed, failed);
        freeMatrix(a, 2); freeMatrix(b, 3); freeMatrix(expected, 2); freeMatrix(c, 2);
    }
    {
        // 2x3 * 3x4 -> 2x4 (неквадратные, разные размеры)
        const int da[] = { 1, 0, 2, 0, 1, 3 };
        const int db[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        const int de[] = { 19, 22, 25, 28, 32, 36, 40, 44 };
        int** a = makeMatrix(2, 3, da);
        int** b = makeMatrix(3, 4, db);
        int** expected = makeMatrix(2, 4, de);
        int** c = multiplyMatrices(a, 2, 3, b, 3, 4);
        assertTest("TC44: Размерность результата rowsA x colsB (2x3 * 3x4 = 2x4)", c != nullptr && areMatricesEqual(c, expected, 2, 4), "Неверный результат 2x4", passed, failed);
        freeMatrix(a, 2); freeMatrix(b, 3); freeMatrix(expected, 2); freeMatrix(c, 2);
    }
    {
        // 1x1 * 1x1
        const int da[] = { 6 };
        const int db[] = { 7 };
        int** a = makeMatrix(1, 1, da);
        int** b = makeMatrix(1, 1, db);
        int** c = multiplyMatrices(a, 1, 1, b, 1, 1);
        assertTest("TC45: BVA min: 1x1 * 1x1 (6 * 7 = 42)", c != nullptr && c[0][0] == 42, "Ожидалось 42", passed, failed);
        freeMatrix(a, 1); freeMatrix(b, 1); freeMatrix(c, 1);
    }
    {
        // строка * столбец -> 1x1 (скалярное произведение)
        const int da[] = { 1, 2, 3 };
        const int db[] = { 4, 5, 6 };
        int** a = makeMatrix(1, 3, da);
        int** b = makeMatrix(3, 1, db);
        int** c = multiplyMatrices(a, 1, 3, b, 3, 1);
        assertTest("TC46: (1x3) * (3x1) = 1x1: [1,2,3]·[4,5,6] = 32", c != nullptr && c[0][0] == 32, "Ожидалось 32", passed, failed);
        freeMatrix(a, 1); freeMatrix(b, 3); freeMatrix(c, 1);
    }
    {
        // столбец * строка -> 3x3 (внешнее произведение)
        const int da[] = { 1, 2, 3 };
        const int db[] = { 4, 5, 6 };
        const int de[] = { 4, 5, 6, 8, 10, 12, 12, 15, 18 };
        int** a = makeMatrix(3, 1, da);
        int** b = makeMatrix(1, 3, db);
        int** expected = makeMatrix(3, 3, de);
        int** c = multiplyMatrices(a, 3, 1, b, 1, 3);
        assertTest("TC47: (3x1) * (1x3) = 3x3 (внешнее произведение)", c != nullptr && areMatricesEqual(c, expected, 3, 3), "Неверная матрица 3x3", passed, failed);
        freeMatrix(a, 3); freeMatrix(b, 1); freeMatrix(expected, 3); freeMatrix(c, 3);
    }
    {
        // умножение на единичную матрицу: A * E = A
        const int da[] = { 1, 2, 3, 4 };
        const int dE[] = { 1, 0, 0, 1 };
        int** a = makeMatrix(2, 2, da);
        int** e = makeMatrix(2, 2, dE);
        int** c = multiplyMatrices(a, 2, 2, e, 2, 2);
        assertTest("TC48: A * E = A (единичная матрица)", c != nullptr && areMatricesEqual(c, a, 2, 2), "Ожидалась исходная матрица", passed, failed);
        freeMatrix(a, 2); freeMatrix(e, 2); freeMatrix(c, 2);
    }
    {
        // умножение на нулевую матрицу
        const int da[] = { 1, 2, 3, 4 };
        int** a = makeMatrix(2, 2, da);
        int** z = allocateMatrix(2, 2);
        int** zeroRef = allocateMatrix(2, 2);
        int** c = multiplyMatrices(a, 2, 2, z, 2, 2);
        assertTest("TC49: A * 0 = 0 (нулевая матрица)", c != nullptr && areMatricesEqual(c, zeroRef, 2, 2), "Ожидалась нулевая матрица", passed, failed);
        freeMatrix(a, 2); freeMatrix(z, 2); freeMatrix(zeroRef, 2); freeMatrix(c, 2);
    }
    {
        // отрицательные числа
        const int da[] = { -1, 2, 3, -4 };
        const int db[] = { 5, -6, -7, 8 };
        const int de[] = { -19, 22, 43, -50 };
        int** a = makeMatrix(2, 2, da);
        int** b = makeMatrix(2, 2, db);
        int** expected = makeMatrix(2, 2, de);
        int** c = multiplyMatrices(a, 2, 2, b, 2, 2);
        assertTest("TC50: Отрицательные элементы -> [[-19,22],[43,-50]]", c != nullptr && areMatricesEqual(c, expected, 2, 2), "Неверный результат со знаками", passed, failed);
        freeMatrix(a, 2); freeMatrix(b, 2); freeMatrix(expected, 2); freeMatrix(c, 2);
    }
    {
        // некоммутативность: A*B != B*A
        const int da[] = { 1, 2, 3, 4 };
        const int db[] = { 0, 1, 1, 0 };
        int** a = makeMatrix(2, 2, da);
        int** b = makeMatrix(2, 2, db);
        int** ab = multiplyMatrices(a, 2, 2, b, 2, 2);
        int** ba = multiplyMatrices(b, 2, 2, a, 2, 2);
        assertTest("TC51: Некоммутативность: A*B != B*A", ab != nullptr && ba != nullptr && !areMatricesEqual(ab, ba, 2, 2), "Ожидались разные результаты", passed, failed);
        freeMatrix(a, 2); freeMatrix(b, 2); freeMatrix(ab, 2); freeMatrix(ba, 2);
    }
    {
        // BVA по переполнению int: 46340^2 = 2 147 395 600 < INT_MAX
        const int da[] = { 46340 };
        int** a = makeMatrix(1, 1, da);
        int** c = multiplyMatrices(a, 1, 1, a, 1, 1);
        assertTest("TC52: BVA: 46340 * 46340 = 2147395600 (в пределах INT_MAX)", c != nullptr && c[0][0] == 2147395600, "Ожидалось 2147395600", passed, failed);
        freeMatrix(a, 1); freeMatrix(c, 1);
    }
    {
        // невалидные случаи
        const int da[] = { 1, 2, 3, 4, 5, 6 };
        int** a = makeMatrix(2, 3, da);   // 2x3
        int** b = makeMatrix(2, 3, da);   // 2x3 -> colsA(3) != rowsB(2)
        assertTest("TC53: Несовместимые размеры (2x3 * 2x3) -> nullptr", multiplyMatrices(a, 2, 3, b, 2, 3) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC54: a = nullptr -> nullptr", multiplyMatrices(nullptr, 2, 3, b, 3, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC55: b = nullptr -> nullptr", multiplyMatrices(a, 2, 3, nullptr, 3, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC56: rowsA = 0 -> nullptr", multiplyMatrices(a, 0, 3, b, 3, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC57: colsA = 0 -> nullptr", multiplyMatrices(a, 2, 0, b, 3, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC58: rowsB = 0 -> nullptr", multiplyMatrices(a, 2, 3, b, 0, 2) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC59: colsB = 0 -> nullptr", multiplyMatrices(a, 2, 3, b, 3, 0) == nullptr, "Ожидался nullptr", passed, failed);
        assertTest("TC60: Отрицательный размер (rowsA = -1) -> nullptr", multiplyMatrices(a, -1, 3, b, 3, 2) == nullptr, "Ожидался nullptr", passed, failed);
        freeMatrix(a, 2);
        freeMatrix(b, 2);
    }

    cout << "\nРезультаты тестирования: Всего: " << (passed + failed) << " | Успешно: " << passed << " | Провалено: " << failed << endl;
}