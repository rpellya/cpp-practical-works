// Практическая работа 1. Базовые типы данных и конструкции в C++

#include <iostream>
#include <climits>
#include <clocale>
#include <string>

using namespace std;

void showTypeInfo();
bool belongsToInterval(int x, int bottom, int top);
int minValue(int x, int y);
float minValue(float x, float y);
int order(int x);
int getLetterCode(char c);
bool isPrime(int x);
void assertTest(const string& testName, bool condition, const string& details, int& passed, int& failed);
void runEquivalencePartitioningTests();

int main()
{
    setlocale(0, "");

    cout << "Нажмите клавишу для проверки функции:" << endl;
    cout << "i - Информация по примитивным типам" << endl;
    cout << "b - Состоит ли в интервале" << endl;
    cout << "m - Минимальное значение из двух аргументов" << endl;
    cout << "o – Количество знаков числа" << endl;
    cout << "c - Код символа" << endl;
    cout << "p - Проверка на простое число " << endl;
    cout << "t - Запуск набора EP-тестов (Equivalence Partitioning & BVA)" << endl;
    cout << "q, e - Выход из программы" << endl;
    
    char inputUser;
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\nВыберите один из пунктов программы: " << endl;

        cin >> inputUser;
        if (cin.fail()) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(256, '\n'); // убираем символ из буфера
            cout << "Некорректный ввод. Повторите: ";
            continue;
        }
        cin.ignore(256, '\n');

        switch (inputUser)
        {
            case 't':
            {
                runEquivalencePartitioningTests();
                break;
            }
            case 'i':
            {
                showTypeInfo();
                break;
            }
            case 'b':
            {
                int x, bottom, top;

                cout << "Введите значение x: ";
                cin >> x;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> x;
                }

                cout << "Введите нижнюю границу: ";
                cin >> bottom;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> bottom;
                }

                cout << "Введите верхнюю границу: ";
                cin >> top;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> top;
                }

                cin.ignore(256, '\n');

                if (belongsToInterval(x, bottom, top))
                    cout << "Ваше значение " << x << " принадлежит интервалу [" << bottom << ", " << top << "]" << endl;
                else
                    cout << "Ваше значение " << x << " НЕ принадлежит интервалу [" << bottom << ", " << top << "]!" << endl;
                break;
            }
            case 'm':
            {
                int typeInput;

                cout << "Выберите тип аргументов (0 - int, 1 - float)" << endl;

                cin >> typeInput;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> typeInput;
                }
                cin.ignore(256, '\n');

                float x, y;
                
                cout << "Выберите первое число: " << endl;
                cin >> x;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> x;
                }
                cin.ignore(256, '\n');

                cout << "Выберите второе число: " << endl;
                cin >> y;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> y;
                }
                cin.ignore(256, '\n');

                if (typeInput == 1) {
                    cout << "Минимальное значение: " << minValue(x, y) << endl;
                }
                else {
                    cout << "Минимальное значение: " << minValue((int)x, (int)y) << endl;
                }

                break;
            }
            case 'o':
            {
                cout << "Введите целое число: " << endl;

                int x;
                cin >> x;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> x;
                }

                cin.ignore(256, '\n');

                cout << "Количество знаков у вашего числа: " << order(x) << endl;
                break;
            }
            case 'c':
            {
                cout << "Введите символ: " << endl;

                char c;
                cin >> c;

                cin.ignore(256, '\n');

                cout << "Код вашего символа: " << getLetterCode(c) << endl;
                break;
            }
            case 'p':
            {
                cout << "Введите целое число: " << endl;

                int x;
                cin >> x;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Некорректный ввод. Повторите: ";
                    cin >> x;
                }

                cin.ignore(256, '\n');

                if (isPrime(x)) {
                    cout << "Ваше число " << x << " простое" << endl;
                }
                else {
                    cout << "Ваше число " << x << " не является простым" << endl;
                }

                break;
            }
            case 'q':
            case 'e':
            {
                cout << "Выход из программы." << endl;
                exitFlag = true;
                break;
            }
            default: {
                cout << "Увы! Такого пункта нет." << endl;
            }
        }
    }
    return 0;
}

void showTypeInfo()
{
    cout << "Информация по примитивным типам:" << endl;
    cout << "char: size = " << sizeof(char) << " byte, min = " << CHAR_MIN << ", max = " << CHAR_MAX << endl;
    cout << "int: size = " << sizeof(int) << " byte, min = " << INT_MIN << ", max = " << INT_MAX << endl;
    cout << "short: size = " << sizeof(short) << " byte, min = " << SHRT_MIN << ", max = " << SHRT_MAX << endl;
    cout << "long: size = " << sizeof(long) << " byte, min = " << LONG_MIN << ", max = " << LONG_MAX << endl;
    cout << "long long: size = " << sizeof(long long) << " byte, min = " << LLONG_MIN << ", max = " << LLONG_MAX << endl;
}

bool belongsToInterval(int x, int bottom, int top) {
    return (x >= bottom && x <= top);
}

int minValue(int x, int y) {
    return x < y ? x : y;
}

float minValue(float x, float y) {
    return x < y ? x : y;
}

int order(int x) {
    if (x == 0) return 1;

    long long value = x;
    if (value < 0) {
        value = -value;
    }
    
    int count = 0;
    while (value > 0) {
        value = value / 10;
        count++;
    }

    return count;
}

int getLetterCode(char c)
{
    return (int)c;
}

bool isPrime(int x) {
    if (x < 2) return false;

    if (x <= 3) return true;

    if (x % 2 == 0 || x % 3 == 0) return false;
    
    for (int i = 5; i <= x / i; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

void assertTest(const string& testName, bool condition, const string& details, int& passed, int& failed) {
    if (condition) {
        cout << "  [PASS] " << testName << endl;
        passed++;
    } else {
        cout << "  [FAIL] " << testName;
        if (!details.empty()) {
            cout << " -> " << details;
        }
        cout << endl;
        failed++;
    }
}

void runEquivalencePartitioningTests() {
    int passed = 0;
    int failed = 0;

    cout << "ЗАПУСК АВТОТЕСТОВ (Equivalence Partitioning & BVA)" << endl;

    cout << "\n--- [1] Тесты: belongsToInterval(x, bottom, top) ---" << endl;
    assertTest("TC1: Внутри интервала (x=25, [10, 50])", belongsToInterval(25, 10, 50) == true, "Ожидалось true", passed, failed);
    assertTest("TC2: Левая граница BVA (x=10, [10, 50])", belongsToInterval(10, 10, 50) == true, "Ожидалось true", passed, failed);
    assertTest("TC3: Правая граница BVA (x=50, [10, 50])", belongsToInterval(50, 10, 50) == true, "Ожидалось true", passed, failed);
    assertTest("TC4: Вне диапазона слева (x=9, [10, 50])", belongsToInterval(9, 10, 50) == false, "Ожидалось false", passed, failed);
    assertTest("TC5: Вне диапазона справа (x=51, [10, 50])", belongsToInterval(51, 10, 50) == false, "Ожидалось false", passed, failed);
    assertTest("TC6: Отрицательный диапазон (x=-5, [-10, 0])", belongsToInterval(-5, -10, 0) == true, "Ожидалось true", passed, failed);
    assertTest("TC7: Инвертированные границы (x=15, [50, 10])", belongsToInterval(15, 50, 10) == false, "Ожидалось false", passed, failed);

    cout << "\n--- [2] Тесты: minValue(x, y) [int & float] ---" << endl;
    assertTest("TC8: int: x < y (3, 7)", minValue(3, 7) == 3, "Ожидалось 3", passed, failed);
    assertTest("TC9: int: x > y (10, 4)", minValue(10, 4) == 4, "Ожидалось 4", passed, failed);
    assertTest("TC10: int: x == y (5, 5)", minValue(5, 5) == 5, "Ожидалось 5", passed, failed);
    assertTest("TC11: int: Отрицательные (-10, -3)", minValue(-10, -3) == -10, "Ожидалось -10", passed, failed);
    assertTest("TC12: float: x < y (2.5f, 5.8f)", minValue(2.5f, 5.8f) == 2.5f, "Ожидалось 2.5f", passed, failed);
    assertTest("TC13: float: x > y (9.1f, 1.4f)", minValue(9.1f, 1.4f) == 1.4f, "Ожидалось 1.4f", passed, failed);
    assertTest("TC14: float: Отрицательные (-3.14f, -2.71f)", minValue(-3.14f, -2.71f) == -3.14f, "Ожидалось -3.14f", passed, failed);


    cout << "\n--- [3] Тесты: order(x) (Количество знаков) ---" << endl;
    assertTest("TC15: Ноль (x=0)", order(0) == 1, "Ожидалось 1", passed, failed);
    assertTest("TC16: Однозначное положительное (x=7)", order(7) == 1, "Ожидалось 1", passed, failed);
    assertTest("TC17: Двузначное положительное (x=42)", order(42) == 2, "Ожидалось 2", passed, failed);
    assertTest("TC18: Многозначное положительное (x=123456)", order(123456) == 6, "Ожидалось 6", passed, failed);
    assertTest("TC19: Однозначное отрицательное (x=-8)", order(-8) == 1, "Ожидалось 1", passed, failed);
    assertTest("TC20: Многозначное отрицательное (x=-9876)", order(-9876) == 4, "Ожидалось 4", passed, failed);
    assertTest("TC21: BVA max: INT_MAX (2147483647)", order(INT_MAX) == 10, "Ожидалось 10", passed, failed);
    assertTest("TC22: BVA min: INT_MIN (-2147483648)", order(INT_MIN) == 10, "Ожидалось 10", passed, failed);

    cout << "\n--- [4] Тесты: getLetterCode(c) (Код символа) ---" << endl;
    assertTest("TC23: Заглавная латиница ('A')", getLetterCode('A') == 65, "Ожидалось 65", passed, failed);
    assertTest("TC24: Строчная латиница ('z')", getLetterCode('z') == 122, "Ожидалось 122", passed, failed);
    assertTest("TC25: Цифровой символ ('0')", getLetterCode('0') == 48, "Ожидалось 48", passed, failed);
    assertTest("TC26: Пробельный символ (' ')", getLetterCode(' ') == 32, "Ожидалось 32", passed, failed);

    cout << "\n--- [5] Тесты: isPrime(x) (Простые числа) ---" << endl;
    assertTest("TC27: Число < 2 (x=1)", isPrime(1) == false, "Ожидалось false", passed, failed);
    assertTest("TC28: Ноль (x=0)", isPrime(0) == false, "Ожидалось false", passed, failed);
    assertTest("TC29: Отрицательное (x=-7)", isPrime(-7) == false, "Ожидалось false", passed, failed);
    assertTest("TC30: Первое простое BVA (x=2)", isPrime(2) == true, "Ожидалось true", passed, failed);
    assertTest("TC31: Второе простое BVA (x=3)", isPrime(3) == true, "Ожидалось true", passed, failed);
    assertTest("TC32: Составное четное BVA (x=4)", isPrime(4) == false, "Ожидалось false", passed, failed);
    assertTest("TC33: Нечетное простое (x=17)", isPrime(17) == true, "Ожидалось true", passed, failed);
    assertTest("TC34: Нечетное составное (x=25)", isPrime(25) == false, "Ожидалось false", passed, failed);
    assertTest("TC35: Большое простое (x=97)", isPrime(97) == true, "Ожидалось true", passed, failed);
    assertTest("TC36: Большое составное (x=100)", isPrime(100) == false, "Ожидалось false", passed, failed);

    cout << "РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ: Всего: " << (passed + failed)
         << " | Успешно: " << passed
         << " | Провалено: " << failed << endl;
}
