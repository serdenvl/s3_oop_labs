// s3_oop_labs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

#include "some_vector.h"
using namespace some_namespace;

void do_stuffs()
{
    some_vector a(1, 2, 3);
    some_vector b(4, 5, 6);
    cout << endl;

    cout << a << " + " << b << " = " << sum_vectors(a, b) << endl;
    cout << a << " - " << b << " = " << sub_vectors(a, b) << endl;
    cout << a << " * " << b << " = " << prod_vectors(a, b) << endl;

    cout << endl;

    cout << "cos " << a << " ^ " << b << " = " << cos_between_vectors(a, b) << endl;
    cout << "sin " << a << " ^ " << b << " = " << sin_between_vectors(a, b) << endl;
    cout << "ang " << a << " ^ " << b << " = " << angle_between_vectors(a, b) << endl;

    cout << endl;

    some_vector c(5, 0, 0);

    cout << c << " * " << 5 << " = " << c.scalar_prod(5) << endl;
    cout << "vector " << c;
    cout << " len " << c.len();
    cout << " norm " << c.norm() << endl;

    cout << endl;
}

int main()
{
    do_stuffs();
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
