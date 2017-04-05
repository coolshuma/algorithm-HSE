#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int n = 5; // Размер матрицы
const int n_num = 4; // Программа работает только с квадратными матрицами,
// а переписать не успевал, поэтому добавил такую константу, которой ограничиваю кол-во строк,
// которые нужно выводить

double a[10][10];

void add(int s1, int s2, double k, string type)
{
    if (type == "st")
        for (int j = 0; j < n; j++)
            a[s1][j] += a[s2][j] * k;
    else
        for (int i = 0; i < n; i++)
            a[i][s1] += a[i][s2] * k;
}

void swap(int s1, int s2, string type)
{
    if (type == "st")
        for (int j = 0; j < n; j++)
            swap(a[s1][j], a[s2][j]);
    else
        for (int i = 0; i < n; i++)
            swap(a[i][s1], a[i][s2]);
}

void div(int s1, double k, string type)
{
    if (type == "st")
        for (int j = 0; j < n; j++)
            a[s1][j] /= k;
    else
        for (int i = 0; i < n; i++)
            a[i][s1] /= k;
}

void mult(int s1, double k, string type)
{
    if (type == "st")
        for (int j = 0; j < n; j++)
            a[s1][j] *= k;
    else
        for (int i = 0; i < n; i++)
            a[i][s1] *= k;
}

void write()
{
    cout << "\\[" << endl << "\\begin{pmatrix}" << endl;
    for (int i = 0; i < n_num; i++)
    {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == -0)
                cout << 0;
            else
                cout << a[i][j];
            if (j == n - 1)
                cout << " \\\\";
            else
                cout << " & ";
        }
        cout << endl;
    }
    cout << "\\end{pmatrix}" << endl << "\\]" << endl ;

    cout << endl;
}


int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    string s, type;

    cout << fixed << setprecision(0);

    write();

    while (cin >> s)
    {
        cin >> type;

        if (s == "swap")
        {
            int s1, s2;
            cin >> s1 >> s2;
            s1--; s2--;
            swap(s1, s2, type);
            cout << "Поменяем местами " << s1 + 1;
            if (type == "st")
                cout << "-ую и "  << s2 + 1 << "-ую строку";
            else
                cout << "-ый и " << s2 + 1 << "-ый столбец";

            cout << ':' << endl;

        }

        if (s == "add")
        {
            int s1, s2; double k;
            cin >> s1 >> s2 >> k;
            s1--; s2--;
            add(s1, s2, k, type);
            cout << "Добавим к " << s1 + 1;
            if (type == "st")
                cout << "-ой строке "  << s2 + 1 << "-ую, домноженную на ";
            else
                cout << "-ому столбцу " << s2 + 1 << "-ый, домноженный на";

            cout << k << ':' << endl;
        }

        if (s == "div")
        {
            int s1; double k;
            cin >> s1 >> k;
            s1--;
            div(s1, k, type);
            cout << "Разделим " << s1 + 1;
            if (type == "st")
                cout << "-ую строку на ";
            else
                cout << "-ый столбец на ";

            cout << k << ':' << endl;
        }

        if (s == "mult")
        {
            int s1; double k;
            cin >> s1 >> k;
            s1--;
            mult(s1, k, type);
            cout << "Домножим " << s1 + 1;
            if (type == "st")
                cout << "-ую строку на ";
            else
                cout << "-ый столбец на ";

            cout << k << ':' << endl;
        }

        cout << endl;

        write();
    }

    return 0;
}


