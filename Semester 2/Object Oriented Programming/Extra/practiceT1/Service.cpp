#include "Service.h"

Service::Service()
{
	this->repo.test_add();
	generate_cars();
}

Service::~Service()
{
	
}

int Service::add_car(string manufacturer, string model, int year, string color)
{
	
	if (this->repo.find_pos(model,year) != -1)
		return -1;
	Car car = Car(manufacturer, model, year, color);
	this->repo.add_car(car);
	return 0;
}
void Service::remove_car(string model, int year)
{
	int pos = this->repo.find_pos(model, year);
	if (pos == -1)
		return;
	this->repo.remove_car(pos);
}
DynamicVector<Car> Service::sort_by_manu_and_model()
{
	DynamicVector <Car> arr = this->repo.get_cars();
	for (int i = 0; i < arr.get_size() - 1; i++)
		for (int j = i; j < arr.get_size(); j++)
		{

		
			if (arr[i].get_manufacturer() > arr[j].get_manufacturer())
			{
				Car aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
			else if (arr[i].get_manufacturer() == arr[j].get_manufacturer())
			{
				if (arr[i].get_model() > arr[j].get_model())
				{
					Car aux = arr[i];
					arr[i] = arr[j];
					arr[j] = aux;
				}
			}

		}	
	
	return arr;
}
void Service::generate_cars()
{
	add_car("Fiat","Idea",2003,"blue");
	add_car("Fiat", "Bravo", 2007, "red");
	add_car("Audi", "A5", 2007, "pink");
	add_car("adfg","TR", 1953, "white");
	add_car("Asup", "sup", 1899, "blue");
		
}

DynamicVector<Car> Service::sort_by_color()
{
	DynamicVector <Car> arr = this->repo.get_cars();
	DynamicVector <Car> filtered_arr;
	for (int i = 0; i < arr.get_size(); i++)
		if (2024 - arr[i].get_year() > 45)
			filtered_arr.add(arr[i]);

	for(int  i = 0; i < filtered_arr.get_size()-1;i++)
		for(int j =i; j< filtered_arr.get_size();j++)
			if (filtered_arr[i].get_color() > filtered_arr[j].get_color())
			{
				Car aux = filtered_arr[i];
				filtered_arr[i] = filtered_arr[j];
				filtered_arr[j] = aux;
			}
	return filtered_arr;
}

