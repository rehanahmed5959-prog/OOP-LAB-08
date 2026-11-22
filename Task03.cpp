#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Product {
protected:
    string name;
    double basePrice;

public:
    Product(const string& name, double basePrice)
        : name(name), basePrice(basePrice) {}

    string getName() const {
        return name;
    }

    virtual double price() const = 0;

    virtual ~Product() = default;
};

class Book : public Product {
public:
    Book(const string& name, double basePrice)
        : Product(name, basePrice) {}

    double price() const override {
        return basePrice;
    }
};

class Electronics : public Product {
public:
    Electronics(const string& name, double basePrice)
        : Product(name, basePrice) {}

    double price() const override {
        return basePrice * 1.17;
    }
};

class Cart {
private:
    Product* items[10]{};
    int count = 0;

public:
    Cart() = default;
    Cart(const Cart&) = delete;
    Cart& operator=(const Cart&) = delete;

    ~Cart() {
        for (int i = 0; i < count; ++i) {
            delete items[i];
        }
    }

    Cart& operator+=(Product* p) {
        if (count >= 10) {
            cout << "Cart is full!\n";
            return *this;
        }
        if (p != nullptr) {
            items[count++] = p;
        }
        return *this;
    }

    Product* operator[](int i) const {
        if (i < 0 || i >= count) {
            return nullptr;
        }
        return items[i];
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < count; ++i) {
            sum += items[i]->price();
        }
        return sum;
    }

    friend ostream& operator<<(ostream& os, const Cart& cart) {
        os << fixed << setprecision(2);
        for (int i = 0; i < cart.count; ++i) {
            os << i + 1 << ". " << cart.items[i]->getName()
               << " - $" << cart.items[i]->price() << '\n';
        }
        os << "Total: $" << cart.total() << '\n';
        return os;
    }
};

int main() {
    Cart cart;

    cart += new Book("Clean Code", 40.00);
    cart += new Electronics("Mechanical Keyboard", 100.00);
    cart += new Electronics("Wireless Mouse", 50.00);

    cout << cart << '\n';

    if (cart[1] != nullptr) {
        cout << "cart[1] name: " << cart[1]->getName() << '\n';
    }

    cout << "cart[5] is nullptr: " << boolalpha
         << (cart[5] == nullptr) << '\n';

    return 0;
}