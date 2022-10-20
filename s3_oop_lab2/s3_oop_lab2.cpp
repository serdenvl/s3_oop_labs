// s3_oop_lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "some_matrix.h"

using namespace std;
using namespace some_namespace;

void do_stuffs()
{
    some_matrix e(4, [&](auto i, auto j) {return i == j; });
    some_matrix a(4, 5, [&](auto i, auto j) {return i + j; });
    some_matrix b(4, 5, [&](auto i, auto j) {return i * j; });

    some_matrix c;
    some_matrix d(c);

    cout << "e: " << endl << e << endl;
    cout << "a: " << endl << a << endl;
    cout << "b: " << endl << b << endl;

    cout << "a.max: " << a.max() << endl;
    cout << "a.min: " << a.min() << endl;

    cout << endl;

    cout << "a+b: " << (a.is_suitable_for_addiction(b) ? "(possible)" : "(impossible)") << endl;
    try
    {
        cout << a + b << endl;
    }
    catch (logic_error err)
    {
        cout << "error: " << err.what() << endl;
    }

    cout << "a-b: " << (a.is_suitable_for_addiction(b) ? "(possible)" : "(impossible)") << endl;
    try
    {
        cout << a - b << endl;
    }
    catch (logic_error err)
    {
        cout << "error: " << err.what() << endl;
    }

    cout << "e*a: " << (e.is_suitable_for_multiplication(a) ? "(possible)" : "(impossible)") << endl;
    try
    {
        cout << e * a << endl;
    }
    catch (logic_error err)
    {
        cout << "error: " << err.what() << endl;
    }

    cout << "a*e: " << (a.is_suitable_for_multiplication(e) ? "(possible)" : "(impossible)") << endl;
    try
    {
        cout << a * e << endl;
    }
    catch(logic_error err)
    {
        cout <<"error: " << err.what() << endl;
    }

    cout << endl;
}

int main()
{
    try
    {
        do_stuffs();
    }
    catch (exception err)
    {
        cout << "\nerror: " << err.what() << endl;
        if (0)
            throw;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
