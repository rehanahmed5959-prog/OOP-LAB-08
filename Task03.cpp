#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    string name;
    double basePrice;

public:
    Product(string n, double p) {
        name = n;
        basePrice = p;
    }

    string getName() const {
        return name;
    }

    virtual double price() = 0;

    virtual ~Product() {}
};

class Book : public Product {
public:
    Book(string n, double p) : Product(n, p) {}

    double price() override {
        return basePrice;
    }
};

class Electronics : public Product {
public:
    Electronics(string n, double p) : Product(n, p) {}

    double price() override {
        return basePrice * 1.17;
    }
};

class Cart {
private:
    Product* items[10];
    int count;

public:
    Cart() {
        count = 0;
    }

    Cart& operator+=(Product* p) {
        if (count >= 10) {
            cout << "Cart is full!" << endl;
        } else {
            items[count] = p;
            count++;
        }
        return *this;
    }

    Product* operator[](int i) {
        if (i < 0 || i >= count) {
            return nullptr;
        }
        return items[i];
    }

    double total() {
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum = sum + items[i]->price();
        }
        return sum;
    }

    friend ostream& operator<<(ostream& out, Cart& c);
};

ostream& operator<<(ostream& out, Cart& c) {
    out << "Cart:" << endl;
    for (int i = 0; i < c.count; i++) {
        out << "  " << c.items[i]->getName() << " : Rs. " << c.items[i]->price() << endl;
    }
    out << "  Total : Rs. " << c.total() << endl;
    return out;
}

int main() {

    Cart cart;
    Product* b  = new Book("C++ Primer", 2500);
    Product* e1 = new Electronics("Headphones", 4000);
    Product* e2 = new Electronics("USB Drive", 1000);

    cart += b;
    cart += e1;
    cart += e2;

    cout << cart;

    cout << "Second item: " << cart[1]->getName() << endl;

    if (cart[5] == nullptr) {
        cout << "cart[5] does not exist" << endl;
    }

    delete b;
    delete e1;
    delete e2;
    return 0;
}