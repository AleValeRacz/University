#pragma once
#include "repository.h"
#include "OperationsStack.h"
typedef struct
{
	Repository* repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
}Service;

Service* create_service(Repository* r, OperationsStack* undoS, OperationsStack* redoS);
void destroy_service(Service* s);
void remove_medicine_serv(Service* s, char* name, double concentration);
void update_medicine_serv(Service* s, char* name, double concentration, int quantity, double price);
int add_medicine_serv(Service* s, char* name, double concentration, int quantity, double price);
Repository* get_repo(Service* s);
int undo(Service* s);
int redo(Service* s);
DynamicArray* search_medicines_by_name(Service* service, const char* substring);
DynamicArray* find_medicines_in_short_supply(Service* service, int threshold);
void sort_by_name(DynamicArray* arr);
void sort_medicines_alphabetically(DynamicArray* arr);
void test_service();