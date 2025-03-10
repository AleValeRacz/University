#include "domain.h"

double ElectricEngine::getPrice()const
{
	return this->basePrice + this->autonomy * 0.01;
}
string ElectricEngine::toString()const
{
	stringstream buffer;
	buffer << "Electric " << this->getPrice() << " " << this->autonomy << endl;
	return buffer.str();
}

double TurboEngine::getPrice()const
{
	return this->basePrice + 100;
}
string TurboEngine::toString()const
{
	stringstream buffer;
	buffer << "Turbo " << this->getPrice() << endl;
	return buffer.str();
}

double Car::computePrice()
{
	if (this->bodyStyle == "Sedan")
		return this->engine->getPrice() + 8000;
	else if (this->bodyStyle == "Convertable")
		return this->engine->getPrice() + 9000;
	return 8000;
}