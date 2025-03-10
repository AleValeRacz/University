#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class Engine {
protected:
    string fuel_type;
    double base_price;

public:
    Engine(string fuel_type, double base_price) : fuel_type(fuel_type), base_price(base_price) {}

    virtual double calculate_price()const
    {
        return 3000;
    }
    virtual string toString() const = 0;

    virtual ~Engine() {}
};

class ElectricEngine : public Engine {
private:
    double autonomy;

public:
    ElectricEngine(string fuel_type, double autonomy) : Engine(fuel_type, 3000), autonomy(autonomy) {}

    double calculate_price() const override;

    string toString() const override;

};

class TurboEngine : public Engine {
public:
    TurboEngine(string fuel_type) : Engine(fuel_type, 3000) {}

    double calculate_price() const override {
        if (fuel_type == "Gasoline") {
            return base_price + 100;
        }
        else if (fuel_type == "Diesel") {
            return base_price + 15;
        }
        else {
            return base_price;
        }
    }

    string toString() const override {
        stringstream ss;
        ss << "Engine Type: Turbo, Fuel Type: " << fuel_type;
        return ss.str();
    }
};

class Car {
private:
    string body_style;
    Engine* engine;

public:
    Car(string body_style, Engine* engine) : body_style(body_style), engine(engine) {}

    double calculate_price() const {
        return engine->calculate_price() + (body_style == "Convertible" ? 1000 : 0);
    }

    void display() const {
        cout << "Body Style: " << body_style << ", " << engine->toString() << endl;
    }

    ~Car() {
        delete engine;
    }
};

