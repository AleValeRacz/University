#include "Service.h"

double Service::addCar(string bodyStyle, string EngineType, int autonomy)
{
	if (EngineType == "Turbo")
	{
		TurboEngine* e = new TurboEngine(3000);
		Car* car = new Car(bodyStyle, e);
		this->cars.push_back(car);
		return car->computePrice();

	}
	else
	{
		ElectricEngine* e = new ElectricEngine(3000, autonomy);
		Car* car = new Car(bodyStyle, e);
		this->cars.push_back(car);
		return car->computePrice();
	}
}
void Service::initial_input()
{
	TurboEngine* e = new TurboEngine(3000);
	Car* car = new Car("Sedan", e);
	ElectricEngine* e2 = new ElectricEngine(3000, 100);
	Car* car2 = new Car("Convertable", e2);
	ElectricEngine* e3 = new ElectricEngine(3000, 80);
	Car* car3 = new Car("Sedan", e3);
	this->cars.push_back(car);
	this->cars.push_back(car2);
	this->cars.push_back(car3);
}

vector<Car*>Service::getCarsWithMaxPrice(double maxPrice)
{
	vector<Car*> vec;
	for (int i = 0; i < this->cars.size(); i++)
		if (this->cars[i]->computePrice() < maxPrice)
			vec.push_back(this->cars[i]);
	return vec;
}

void Service::writeToFile(string filename, double maxPrice)
{
	ofstream fout(filename);
	vector<Car*> vec = this->getCarsWithMaxPrice(maxPrice);
	for (int i = 0; i <vec.size(); i++)
		fout<< vec[i]->get_bodystyle() << " " << vec[i]->get_engine()->toString()<<" "<<vec[i]->computePrice()<<endl;

}
