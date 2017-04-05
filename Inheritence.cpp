#include <iostream>
#include <vector>
using namespace std;

class Figure {
private:
public:

    virtual void Draw() {
        cout << "SampleFigure" << endl;
    }

};

class Rectangle : public Figure {
private:
    int length, width;
public:
    Rectangle(int a, int b) : length(a), width(b) {}
    void Draw() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                cout << '*';
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Square : public Figure {
private:
    int length;
public:
    Square (int a) : length(a) {}
    void Draw() {
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                cout << '*';
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Circle : public Figure {
private:
    int radius;
public:
    Circle (int a) : radius(a) {}
    void Draw() {
        for (int i = 0; i < radius * 2; ++i) {
            int left;
            int right;
            if (i <= radius) {
                left = radius - i - 1;
                right = radius + i + 1;
            } else {
                left = 0 + (i - radius) ;
                right = (2 * radius) - (i - radius) ;
            }
            for (int j = 0; j < radius * 2; ++j) {
                if (j >= left && j <= right)
                    cout << '*';
                else
                    cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Triangle : public Figure {
private:
    int a;
    int b;
    int c;
public:
    Triangle (int one, int two, int three) : a(one), b(two), c(three) {}
    void Draw() {
        for (int i = 0; i < a; ++i) {
            int left = b / 2 - (i + 1) / 2;
            int right = b / 2 + (i + 1) / 2;
            for (int j = 0; j < b; ++j) {
                if (j >= left && j <= right)
                    cout << '*';
                else
                    cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
};

void Factory(vector <Figure*>& v) {
    string s;
    while (cin >> s) {
        if (s[0] == 'R') {
            int a;
            int b;
            cin >> a >> b;
            v.push_back(new Rectangle(a, b));
        }
        if (s[0] == 'T') {
            int a;
            int b;
            int c;
            cin >> a >> b >> c;
            v.push_back(new Triangle(a, b, c));
        }
        if (s[0] == 'C') {
            int a;
            cin >> a;
            v.push_back(new Circle(a));
        }
        if (s[0] == 'S') {
            int a;
            cin >> a;
            v.push_back(new Square(a));
        }
    }
}

int main() {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);

    vector<Figure*> v;

    Rectangle r1(2, 3);
    Rectangle r2(7, 5);
    Square s1(2);
    Square s2(5);
    Triangle t(8, 15, 6);
    Circle c1(8);

    v.push_back(&r1);
    v.push_back(&r2);
    v.push_back(&s1);
    v.push_back(&s2);
    v.push_back(&t);
    v.push_back(&c1);

    Factory(v);

    for (auto f : v) {
        f->Draw();
    }

    for (auto f : v) {
        delete f;
    }
}

