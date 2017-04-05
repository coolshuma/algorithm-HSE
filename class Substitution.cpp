#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Substitution {
private:
    vector <int> data;
public:
    Substitution(vector<int> my_vector) : data(my_vector){}
    Substitution(initializer_list<int> my_init_list) : data(my_init_list){}

    Substitution& operator *= (const Substitution& other) {
        for (size_t i = 0; i < data.size(); ++i){
            data[i] = other.data[data[i] - 1];
        }
        return *this;
    }

    Substitution operator *(const Substitution& other) {
        Substitution temp = *this;
        temp *= other;
        return temp;
    }

    Substitution& pow(int degree) {
        if (degree > 0) {
            Substitution my_substitution = *this;
            for (int i = 0; i < degree - 1; ++i) {
                *this *= my_substitution;
            }
            return *this;
        } else {
            Substitution my_substitution = *this;
            for (size_t i = 0; i < data.size(); ++i) {
                data[my_substitution[i] - 1] = i + 1;
            }
            return *this;
        }
    }

    size_t size() const {
        return data.size();
    }

    int& operator[](int i) {
        return data[i];
    }

    const int& operator[](int i) const{
        return data[i];
    }

    void cout_in_latex() {
        cout << "\\[" << endl  << "\\begin{pmatrix}" << endl;
        for (int i = 0; i < data.size(); ++i) {
            cout << i + 1 << ' ';
            if (i != data.size() - 1) {
                cout << "& ";
            } else {
                cout << "\\\\";
            }
        }
        cout << endl;
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i] << ' ';
            if (i != data.size() - 1) {
                cout << "& ";
            } else {
                cout << "\\\\";
            }
        }
        cout << endl;
        cout << "\\end{pmatrix}" << endl << "\\]" << endl ;

    }

};

ostream& operator <<(ostream& os, const Substitution my_substitution) {
    for (int i = 0; i < my_substitution.size(); ++i) {
        cout << i + 1 << ' ';
    }
    cout << endl;
    for (int i = 0; i < my_substitution.size(); ++i) {
        cout << my_substitution[i] << ' ';
    }
    cout << endl;
}

int main() {
    freopen("out", "w", stdout);
    Substitution a = {5, 8, 1, 3, 2, 7, 6, 4};
    a.pow(-1);
    cout << a;
    Substitution b = {3, 5, 4, 8, 1, 7, 6, 2};
    a *= b;
    Substitution x = {4, 8, 2, 5, 3, 1, 6, 7};
    a.pow(145);
    a *= x;
    cout << a;
    a.cout_in_latex();
}

