#pragma warning(disable: 4996)
#include "domain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Medicine* create_medicine(char* name, double concentration, int quantity, double price)
{
	Medicine* m = (Medicine*)malloc(sizeof(Medicine));
	if (m == NULL)
		return NULL;
	m->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	if (m->name == NULL)
	{
		free(m);
		return NULL;
	}
	strcpy(m->name, name);
	m->concentration = concentration;
	m->quantity = quantity;
	m->price = price;
	return m;

}	
void destroy_medicine(Medicine* m)
{
	free(m->name);
	free(m);
}

char* get_name(Medicine* m)
{
	return m->name;
}
double get_concentration(Medicine* m)
{
	return m->concentration;
}
int get_quantity(Medicine* m)
{
	return m->quantity;
}
double get_price(Medicine* m)
{
	return m->price;

}
void to_string(Medicine* m, char str[])
{
	sprintf(str, "Name: %s, Concentration: %lf, Quantity: %d, Price: %lf ", m->name, m->concentration, m->quantity, m->price);

}
Medicine* copy_medicine(Medicine* m)
{
	if (m == NULL)
		return NULL;
	Medicine* new_med = create_medicine(get_name(m), get_concentration(m), get_quantity(m), get_price(m));
	return new_med;

}
