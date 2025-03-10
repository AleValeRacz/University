#pragma once
#include "C:\Users\Ale\Documents\GitHub\oop-a4-5-916-Racz-Alexandra\.vs\A4\A4\dynamic_vector.h"
#include "Car.h"
class Repo

{
private:

	DynamicVector <Car> cars;
public:
	Repo();
	~Repo();
	void add_car(Car &c);
	void remove_car(int pos);
	DynamicVector<Car> get_cars();
	int find_pos(string model, int year);
	void test_add();
};

