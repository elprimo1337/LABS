#include "Fraction.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f1 + f2 = " << f1 + f2 << endl;
    cout << "f1 - f2 = " << f1 - f2 << endl;
    cout << "f1 * f2 = " << f1 * f2 << endl;
    cout << "f1 / f2 = " << f1 / f2 << endl;
    cout << "f1 > f2: " << (f1 > f2) << endl;
    cout << "f1 < f2: " << (f1 < f2) << endl;
    cout << "f1 == f2: " << (f1 == f2) << endl;
    Fraction f3;
    cout << "Введите дробь (числитель/знаменатель): ";
    cin >> f3;
    cout << "Введенная дробь: " << f3 << endl;

    cout << "Обратная дробь к f1: " << f1.inverse() << endl;

}
