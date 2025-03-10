#pragma once
#include "domain.h"
class Service
{
private:
	vector<Car*> cars;
public:
	Service() { this->initial_input(); }
	~Service() {};
	double addCar(string bodyStyle, string EngineType, int autonomy);
	vector<Car*> getCars() { return this->cars; };
	vector<Car*>getCarsWithMaxPrice(double maxPrice);
	void writeToFile(string file_name, double maxPrice);
	void initial_input();
};








