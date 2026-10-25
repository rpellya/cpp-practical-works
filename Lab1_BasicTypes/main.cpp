// Практическая работа 1. Базовые типы данных и конструкции в C++

#include <iostream>
#include <climits>
#include <clocale>

using namespace std;

void showTypeInfo();
bool belongsToInterval(int x, int bottom, int top);
int minValue(int x, int y);
float minValue(float x, float y);
int order(int x);
int getLetterCode(char c);
bool isPrime(int x);

int main()
{
    setlocale(0, "");

    cout << "Нажмите клавишу для проверки функции:" << endl;
    cout << "t - Информация по примитивным типам" << endl;
    cout << "b - Состоит ли в интервале" << endl;
    cout << "m - Минимальное значение из двух аргументов" << endl;
    cout << "o – Количество знаков числа" << endl;
    cout << "c - Код символа" << endl;
    cout << "p - Проверка на простое число " << endl;
    cout << "q, e - Выход из программы" << endl;
    
    char inputUser;
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\nВыберите один из пунктов программы: " << endl;

        cin >> inputUser;
        if (cin.fail()) {
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