#include <iostream>
using namespace std;

class Fraction {
private:
    int num, den;

    static int gcd(int a, int b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    void simplify() {
        if (den == 0) den = 1;
        if (den < 0) {
            num = -num;
            den = -den;
        }
        int g = gcd(num, den);
        if (g > 1) {
            num /= g;
            den /= g;
        }
    }

public:
    Fraction(int n = 0, int d = 1) {
        num = n;
        den = d;
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
        num = num + den;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Fraction& f);
    friend istream& operator>>(istream& in, Fraction& f);
};

ostream& operator<<(ostream& out, const Fraction& f) {
    out << f.num << "/" << f.den;
    return out;
}

istream& operator>>(istream& in, Fraction& f) {
    int n, d;
    in >> n >> d;
    f = Fraction(n, d); 
    return in;
}

int main() {
    Fraction a(1, 2), b(3, 4);

    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;

    Fraction c(2, 4);
    if (c == a) {
        cout << "2/4 is equal to " << a << endl;
    }

    if (a < b) {
        cout << a << " is less than " << b << endl;
    }

    ++a;
    cout << "After ++a: " << a << endl;

    Fraction f;
    cout << "Enter numerator and denominator: ";
    cin >> f;
    cout << "You entered " << f << endl;

    return 0;
}