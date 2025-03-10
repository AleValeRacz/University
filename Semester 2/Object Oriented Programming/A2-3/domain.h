#pragma once
#include "dynamic_array.h"
typedef struct 
{
	char* name;
	double concentration, price;
	int quantity;
}Medicine;

Medicine* create_medicine(char* name, double concentration, int quantity, double price);
void destroy_medicine(Medicine* m);
char* get_name(Medicine* m);
double get_concentration(Medicine* m);
int get_quantity(Medicine* m);
double get_price(Medicine* m);
void to_string(Medicine* m, char str[]);
Medicine* copy_medicine(Medicine* m);
