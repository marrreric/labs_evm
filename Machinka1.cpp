#include <conio.h>
#include <limits>
#include <iostream>
using namespace std;

static short invBits(short, unsigned, unsigned);
static double invBits(double, unsigned, unsigned);

void printBinary(long long value, size_t bitsCount) {
    for (int i = bitsCount - 1; i >= 0; i--) {
        cout << ((value >> i) & 1);
    }
    cout << endl;
}


void printDoubleToBinary(double dValue) {
    union {
        double a;
        long long b;
    } converter;
    converter.a = dValue;
    printBinary(converter.b, 64);
}

void printMenu() {
    cout << "Меню:\n";
    cout << "1. Ввод типа short int\n";
    cout << "2. Ввод типа double\n";
    cout << "3. Вывод short int числа в двоичном/исходном представлении\n";
    cout << "4. Вывод double числа в двоичном/исходном представлении\n";
    cout << "Инвертирование (от старшего бита к младшему, слева-направо):\n";
    cout << "5. Инвертировать биты в short числе\n";
    cout << "6. Инвертировать биты в double числе\n";
    cout << "0. Выход\n";
    cout << "Выберите опцию: ";
}
int main()
{
    setlocale(LC_ALL, "rus");
    short int s;
    double d;
    short option;
    bool shInited = false, dInited = false;

    do {

        printMenu();


        while (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число от 0 до 6: ";
        }


        switch (option) {
        case 1:
            cout << "Введите значение типа short int: ";
            while (!(cin >> s)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Повторите попытку: ";
            }
            shInited = true;
            break;
        case 2:
            cout << "Введите значение типа double: ";
            while (!(cin >> d)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Повторите попытку: ";
            }
            dInited = true;
            break;
        case 3:
            if (!shInited) {
                cout << "Значение не задано" << endl;
                break;
            }
            cout << "Двоичное представление (short int): ";
            printBinary(static_cast<short>(s), 16);
            cout << "Исходный вид: " << s << endl;
            break;
        case 4:
            if (!dInited) {
                cout << "Значение не задано" << endl;
                break;
            }
            cout << "Двоичное представление (double): ";
            printDoubleToBinary(d);
            cout << "Исходный вид: " << d << endl;
            break;
        case 5:
        {
            if (!shInited) {
                cout << "Значение не задано" << endl;
                break;
            }
            unsigned start, count;
            cout << "Введите начальный индекс и кол-во бит: ";
            while (!(cin >> start >> count)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Повторите попытку: ";
            }
            try {
                s = invBits(s, start, count);
            }
            catch (...) {
                cout << "Некорректные параметры, повторите попытку" << endl;
            }
            break;
        }
        case 6:
        {
            if (!dInited) {
                cout << "Значение не задано" << endl;
                break;
            }
            unsigned start, count;
            cout << "Введите начальный индекс и кол-во бит: ";
            while (!(cin >> start >> count)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некорректный ввод. Повторите попытку: ";
            }
            try {
                d = invBits(d, start, count);
            }
            catch (...) {
                cout << "Некорректные параметры, повторите попытку" << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный ввод. Пожалуйста, введите число от 0 до 6." << endl;

        }
        if (option != 0) {
            system("pause");
            system("cls");
        }
    } while (option != 0);
    return 0;
}


static short invBits(short value, unsigned start, unsigned count) {
    if (count > start + 1 || start >= 16) throw "bad indexes";
    short resVal = value;
    unsigned long long i = 1ULL << start;
    for (; count > 0; count--, i >>= 1) {
        resVal ^= i;
    }
    return resVal;
}

static double invBits(double value, unsigned start, unsigned count) {
    if (count > start + 1 || start >= 64) throw "bad indexes";
    union {
        double val;
        char bytes[sizeof(double)];
    } d = { value };
    unsigned currentBit = sizeof(double) * 8 - 1;
    for (int j = sizeof(double) - 1; j >= 0 && count; j--) {
        for (int i = sizeof(char) * 8 - 1; i >= 0 && count; i--, currentBit--) {
            if (currentBit <= start) {
                d.bytes[j] ^= (1 << i);
                count--;
            }
        }
    }
    return d.val;
}