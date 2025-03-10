#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
class Engine
{
protected:
	double basePrice=3000;
public:
	Engine(double basePrice) : basePrice{ basePrice } {}
	virtual ~Engine() {};
	virtual string toString()const = 0;
	virtual double getPrice()const = 0;

};

class ElectricEngine :public Engine
{
private: 
	int autonomy;
public:
	ElectricEngine(double baseprice, int autonomy) : Engine{ baseprice }, autonomy{ autonomy } {};
	~ElectricEngine() {};
	double getPrice() const override;
	string toString()const override;

};

class TurboEngine :public Engine
{

public:
	TurboEngine(double baseprice) : Engine{ baseprice } {};
	~TurboEngine() {};
	double getPrice() const override;
	string toString()const override;

};

class Car
{
private:
	string bodyStyle;
	Engine *engine;
public:
	Car(string bodyStyle, Engine* engine) : bodyStyle{ bodyStyle }, engine{ engine } {};
	~Car() {};
	Engine* get_engine() { return this->engine; }
	string get_bodystyle() { return this->bodyStyle;}
	double computePrice();
};









