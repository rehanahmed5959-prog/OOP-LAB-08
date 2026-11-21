#include <cstdlib>
#include <iostream>

using namespace std;

class Fraction {
private:
    int num;
    int den;

    static int computeGCD(int a, int b) {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return (a == 0) ? 1 : a;
    }

    void simplify() {
        if (den == 0) {
            den = 1;
        }
        if (den < 0) {
            num = -num;
            den = -den;
        }
        int g = computeGCD(num, den);
        num /= g;
        den /= g;
    }

public:
    Fraction(int n = 0, int d = 1) : num(n), den(d) {
        simplify();
    }


    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }

    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }

    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }

    Fraction& operator++() {
        num += den;
        simplify();
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Fraction& f) {
        out << f.num << '/' << f.den;
        return out;
    }

    friend istream& operator>>(istream& in, Fraction& f) {
        if (in >> f.num >> f.den) {
            f.simplify();
        }
        return in;
    }
};

int main() {
    Fraction a(1, 2);
    Fraction b(3, 4);

    cout << boolalpha;
    cout << "a = " << a << ", b = " << b << '\n';
    cout << "a + b  = " << (a + b) << '\n';
    cout << "a - b  = " << (a - b) << '\n';
    cout << "a * b  = " << (a * b) << '\n';
    cout << "a == b : " << (a == b) << '\n';
    cout << "a < b  : " << (a < b) << '\n';
    cout << "++a    = " << (++a) << '\n';

    Fraction userFrac;
    cout << "\nEnter numerator and denominator: ";
    if (cin >> userFrac) {
        cout << "Simplified fraction: " << userFrac << '\n';
    }

    return 0;
}