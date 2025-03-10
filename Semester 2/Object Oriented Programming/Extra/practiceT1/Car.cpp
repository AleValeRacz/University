#include "Car.h"
#include <iostream>

Car::Car(const string &manufacturer, const string &model, int year, const string &color) :manufacturer{ manufacturer }, model{ model }, year{ year }, color{ color }
{

}

Car::Car(const Car& c)
{
	this->manufacturer = c.manufacturer;
	this->model = c.model;
	this->year = c.year;
	this->color = c.color;
}

Car::~Car()
{
}
