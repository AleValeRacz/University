#pragma once
#include "Repo.h"
class Service
{
private:
	Repo repo;
public:
	Service();
	~Service();
	int add_car(string manufacturer, string model ,int year, string color);
	void remove_car(string,int);
	DynamicVector<Car> get_cars();
	DynamicVector <Car> sort_by_manu_and_model();
	DynamicVector <Car> sort_by_color();
	void generate_cars();
};

