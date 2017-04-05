#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Polynomial {
 private:
    vector <T> coefficients;

 public:
    Polynomial(vector <T> data) : coefficients(data) {
        erase_zeroes();
    }
    Polynomial(T value = T()) {
        coefficients.push_back(value);
        erase_zeroes();
    }
    template <class InputIterator>
    Polynomial(InputIterator begin,  InputIterator end) : coefficients(begin, end) {
        erase_zeroes();
    }

    bool operator==(const Polynomial& other) const {
        if (this->Degree() != other.Degree()) {
            return false;
        }

        for (size_t i = 0; i <= this->Degree(); ++i) {
            if (coefficients[i] != other.coefficients[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    Polynomial& operator+=(const Polynomial& other) {
        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            if (coefficients.size() - 1 < i)
                coefficients.push_back(T());
            coefficients[i] += other.coefficients[i];
        }
        erase_zeroes();
        return *this;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial temp(*this);
        temp += other;
        return temp;
    }

    Polynomial& operator-=(const Polynomial& other) {
        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            if (coefficients.size() - 1 < i)
                coefficients.push_back(T());
            coefficients[i] -= other.coefficients[i];
        }
        erase_zeroes();
        return *this;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial temp(*this);
        temp -= other;
        return temp;
    }

    Polynomial& operator*=(const Polynomial& other) {
        vector<T> multiplied;
        for (size_t i = 0; i < coefficients.size(); ++i) {
            for (size_t j = 0; j < other.coefficients.size(); ++j) {
                while (multiplied.size() < i + j + 1)
                    multiplied.push_back(T());
                multiplied[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        coefficients = multiplied;
        erase_zeroes();
        return *this;
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial temp(*this);
        temp *= other;
        return temp;
    }

    T operator[](int degree) const {
        if (degree > Degree() || degree < 0) {
            return T();
        }
        return coefficients[degree];
    }

    int Degree() const {
        if (coefficients.size() == 1 && coefficients[0] == T())
            return -1;
        else
            return coefficients.size();
    }

    T operator()(const T& point) const {
        if (Degree() < 0)
            return T();
        T value = coefficients[0];
        T cur_point = point;
        for (size_t i = 1; i < coefficients.size(); ++i) {
            value += cur_point * coefficients[i];
            cur_point *= point;
        }
        return value;
    }

    typename vector<T>::const_iterator begin() const {
        return coefficients.begin();
    }

    typename vector<T>::const_iterator end() const {
        if (coefficients.size() == 0)
            return coefficients.end();

        typename vector<T>::const_iterator it = coefficients.end();
        --it;
        while (*it == T() && it != coefficients.begin())
            --it;
        return ++it;
    }

    void erase_zeroes() {
        size_t it = coefficients.size() - 1;
        while (!coefficients.empty() && coefficients[it] == T()) {
            coefficients.pop_back();
            --it;
        }

        if (coefficients.empty())
            coefficients.push_back(T());
    }
};

template <typename T>
bool operator==(const T& v, const Polynomial<T>& b) {
    Polynomial<T> a(v);
    return (a == b);
}

template <typename T>
bool operator!=(const T& v, const Polynomial<T>& b) {
    Polynomial<T> a(v);
    return (a != b);
}

template <typename T>
Polynomial<T> operator+(const T& v, const Polynomial<T>& b)  {
    Polynomial<T> a(v);
    a += b;
    return a;
}

template <typename T>
Polynomial<T> operator-(const T& v, const Polynomial<T>& b)  {
    Polynomial<T> a(v);
    a -= b;
    return a;
}

template <typename T>
Polynomial<T> operator*(const T& v, const Polynomial<T>& b)  {
    Polynomial<T> a(v);
    a *= b;
    return a;
}

template <typename T>
ostream& operator << (ostream& os, const Polynomial<T>& my_polynom) {
    for (int i = my_polynom.Degree(); i >= -1;  --i) {
        if (my_polynom[i] == 0)
            continue;

        if (my_polynom[i] == -1) {
            os << "-";
        } else if (my_polynom[i] > -1 && i != my_polynom.Degree()) {
            os << "+";
        }

        if (my_polynom[i] != 1 && my_polynom[i] != -1) {
            os << my_polynom[i];
            if (i > 0)
                os << '*';
        }

        if (i > 0)
            os << "x";

        if (i > 1)
            os << "^" << i;

        if (i == 0 && (my_polynom[i] == 1 || my_polynom[i] == -1))
            os << 1;
    }
    return os;
}
