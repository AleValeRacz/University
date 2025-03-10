#include "Repo.h"
#include <assert.h>
Repo::Repo()
{
	
	
}
Repo::~Repo()
{
}

void Repo::add_car(Car &c)
{
	this->cars.add(c);
}

void Repo::remove_car(int pos)
{
	this->cars.remove(pos);
}

DynamicVector<Car> Repo::get_cars()
{
	return this->cars;
}
int Repo::find_pos(string model, int year)
{
	int pos = -1;
	for(int i= 0; i < this->cars.get_size();i++)
		if (this->cars[i].get_model() == model && this->cars[i].get_year() == year)
		{
			pos = i;
			break;
		}
	return pos;

}

void Repo::test_add()
{
	Repo repo;
	Car car = Car("Fiat", "Idea", 2003, "blue");
	repo.add_car(car);
	assert(repo.get_cars().get_size() == 1);
}

