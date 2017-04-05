#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
class Array {
private:
    vector<T> data;
public:
    explicit Array (const initializer_list<T>& my_list) : data(my_list) {
    }

    explicit Array (const vector<T>& my_vector) : data(my_vector) {
    }

    Array (size_t number, const T& value) {
        for (size_t i = 0; i < number; ++i) {
            data[i] = value;
        }
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    

    ComplexNumber& operator += (const ComplexNumber& other) { // потому что возвращаем сам элемент
        a += other.a;
        b += other.b;
        return *this;
    }

    ComplexNumber operator +(const ComplexNumber& other) const {
        ComplexNumber C(*this);
        C += other;
        return C;
    }

    ComplexNumber& operator -= (const ComplexNumber& other) {
        a -= other.a;
        b -= other.b;
        return *this;
    }

    ComplexNumber operator - (const ComplexNumber& other) const {
        ComplexNumber C(*this);
        C -= other;
        return C;
    }

    ComplexNumber& operator *= (const ComplexNumber& other) {
        a = a * other.a - b * other.b;
        b = a * other.b + other.a * b;
        return *this;
    }

    ComplexNumber operator *(const ComplexNumber& other) const {
        ComplexNumber C(*this);
        C *= other;
        return C;
    }

    ComplexNumber& operator /= (const ComplexNumber& other) {
        T sqr = other.abs() * other.abs();
        a = (a * other.a + b * other.b) / sqr;
        b = (a * other.b - other.a * b) / sqr;
        return *this;
    }

    ComplexNumber operator /(const ComplexNumber& other) const {
        ComplexNumber C(*this);
        C /= other;
        return C;
    }

    ComplexNumber operator +() const {
        ComplexNumber C(*this);
        return C;
    }

    ComplexNumber operator -() const {
        ComplexNumber C(*this);
        C.a = -a;
        C.b = -b;
        return C;
    }

    T abs() const {
        return sqrt(a * a + b * b);
    }

    T Re() const {
        return a;
    }

    T Im() const {
        return b;
    }

    bool operator == (const ComplexNumber& other) const {
            if ((a == other.a) && (b == other.b)) {
            return true;
        } else {
            return false;
        }
    }

    bool operator != (const ComplexNumber& other) const {
        if ((a == other.a) && (b == other.b)) {
            return false;
        } else {
            return true;
        }
    }
};

template <typename T>
ostream& operator << (ostream& os, const ComplexNumber<T>& c) {
    os << c.Re();
    if (c.Im() >= 0)
        os << '+';
    os << c.Im() << 'i' << endl;
    return os;
}

int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);

    int a1, a2, b1, b2;

    cin >> a1 >> a2 >>  b1 >> b2;

    ComplexNumber<int> a (a1, a2);
    ComplexNumber<int> b (b1, b2);

    cout << a << b;

    a += b;

    cout << a << b;

    a *= b;

    cout << a;

    a /= b;

    cout << a;

    ComplexNumber<int> c = a;
    cout << a << c;

    return 0;
}


