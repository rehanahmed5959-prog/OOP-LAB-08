#include <iostream>
using namespace std;

class Vehicle {
protected:
    string regNo;

public:
    Vehicle() {
        regNo = "Unknown";
    }

    virtual double toll() = 0;
    virtual string type() = 0;

    void show_info() {
        cout << type() << " " << regNo << ": toll Rs. " << toll() << endl;
    }

    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    Car(string r) {
        regNo = r;
    }

    double toll() override {
        return 150.0;
    }

    string type() override {
        return "Car";
    }
};

class Bus : public Vehicle {
public:
    Bus(string reg) {
        regNo = reg;
    }

    double toll() override {
        return 300.0;
    }

    string type() override {
        return "Bus";
    }
};

class Truck : public Vehicle {
public:
    int axiles;

    Truck(string reg, int a) {
        regNo = reg;
        axiles = a;
    }

    double toll() override {
        return 200.0 + (100.0 * axiles);
    }

    string type() override {
        return "Truck";
    }
};

int main() {
    Vehicle* lane[4];
    lane[0] = new Car("LHR-5454");
    lane[1] = new Bus("KHI-777");
    lane[2] = new Truck("AB-3456", 2);
    lane[3] = new Car("QA-5787");

    double totaltoll = 0.0;

    for (int i = 0; i < 4; i++) {
        lane[i]->show_info();
        totaltoll += lane[i]->toll();
    }

    cout << "Total Toll collected: " << totaltoll << endl;

    for (int i = 0; i < 4; i++) {
        delete lane[i];
    }

    return 0;
}