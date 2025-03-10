#pragma once

#include <string>

using namespace std;
class Car
{
private:
	string manufacturer, model, color;
	int year;

public:
	Car(const string &manufacturer = "", const string & model = "", int year = 0, const string &color = "");
	~Car();
	Car(const Car & c);
	string get_manufacturer()const { return manufacturer; }
	string get_model()const { return model; }
	string get_color() const { return color; }
	int get_year() const { return year; }

};

