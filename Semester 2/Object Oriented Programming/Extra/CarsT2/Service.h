#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>
class Service {
private:
    vector<Car*> cars;

public:
    void add_car(Car* car) {
        cars.push_back(car);
        cout << "Car added successfully. Price: $" << car->calculate_price() << endl;
    }

    void show_all_cars() const {
        for (const auto& car : cars) {
            car->display();
        }
    }

    void save_to_file(double max_price, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            vector<Car*> filtered_cars;
            copy_if(cars.begin(), cars.end(), back_inserter(filtered_cars),
                [max_price](Car* car) { return car->calculate_price() < max_price; });

            sort(filtered_cars.begin(), filtered_cars.end(),
                [](Car* car1, Car* car2) { return car1->calculate_price() < car2->calculate_price(); });

            for (const auto& car : filtered_cars) {
                file << "Car: ";
                car->display();
            }
            file.close();
        }
        else {
            cout << "Unable to open file.";
        }
    }

    ~Service() {
        for (auto& car : cars) {
            delete car;
        }
    }
};

