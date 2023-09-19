// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
#include "strings.h"
#include "Regex.h"

int main()
{
    /*
    * Тестирование различных строк на соответствие
    *   регулярным выражениям
    */
    class Regex test;
    char* regex = new char[100];
    char* arg = new char[100];
    strcpy(regex, "[A-Z]1[a-z]1+(tion)1");
    strcpy(arg, "Competition");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "Definition");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "information");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "Intiontio");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    cout << "\n\n";

    strcpy(regex, "[A-Z]1[a-z]1+( )1-2[A-Z]1[a-z]1+( )1-2(8)1[0-9]10");
    strcpy(arg, "Sergey  Ivanoff  80055535356");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergey  Ivanoff  80055535356");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "Sergey  Ivanoff       80055535356");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "Sergey  Ivanoff  90055535356");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    cout << "\n\n";

    strcpy(regex, "[a-z|A-Z|0-9]1+(.)1[a-z|A-Z|0-9]1+(@)1(gmail)1(.)1(com)1");
    strcpy(arg, "sergey.ivanoff1990@gmail.com");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergey.ivanoff.1990@gmail.com");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergey31.ivanoff.1990@gmail.com");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergeyivanoff1990@gmail.com");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergey.ivanoff.1990@mail.ru");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    strcpy(arg, "sergey.ivanoff1990@gmail.us");
    cout << "cmp('" << arg << "','" << regex << "') = " << test.regex_cmp(arg, regex) << endl;
    cout << "\n\n";

    /*
    *  Проверка ошибок в регул. выражениях
    */

    strcpy(regex, "[A-Z]1[a-z]1+(tio");
    cout << "Regex = '" << regex << "'\n";
    test.regex_size(regex);

    strcpy(regex, "[A-Z]1[a-zz]");
    cout << "Regex = '" << regex << "'\n";
    test.regex_size(regex);
    strcpy(regex, "[A-Z](nn)4-6");
    cout << "Regex = '" << regex << "'\n";
    test.regex_size(regex);

    delete[] arg;
    delete[] regex;
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
