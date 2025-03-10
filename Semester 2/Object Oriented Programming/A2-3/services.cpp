#include "services.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include<assert.h>
#pragma warning(disable: 4996)
Service* create_service(Repository* r,  OperationsStack* undoS,OperationsStack* redoS)
{
	Service* s = (Service*)malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = r;
	s->undoStack = undoS;
	s->redoStack = redoS;
	return s;
}
void destroy_service(Service* s)
{

	
	while (!isEmpty(s->undoStack))
	{

		Operation* op = pop(s->undoStack);
		destroyOperation(op);
	}
	
	destroyStack(s->undoStack);
	
	while (!isEmpty(s->redoStack))
	{

		Operation* op1 = pop(s->redoStack);
		destroyOperation(op1);
	}
	
	destroyStack(s->redoStack);
	destroy_repository(s->repo);
	free(s);
}
int add_medicine_serv(Service* s, char* name, double concentration, int quantity, double price)
{
	char op_name[50];
	Medicine* m = create_medicine(name, concentration, quantity, price);
	Medicine* tester = find(get_repo(s), name, concentration);
	if (tester != NULL)
	{
		Medicine* m = create_medicine(name, concentration, quantity + get_quantity(tester), get_price(tester));
		update_medicine(get_repo(s), find_position(get_repo(s), tester),m);

		return 2;
	}
	int res = add_medicine(s->repo, m);

	strcpy(op_name, "add");
	Operation* operation1 = createOperation(m,op_name);
	push(s->undoStack, operation1);

	return res;


}
void remove_medicine_serv(Service* s, char* name, double concentration)
{
	Medicine* m = find(get_repo(s), name, concentration);
	if (m == NULL)
		return;

	int pos = find_position(get_repo(s), m);
	delete_medicine(get_repo(s), pos);
	char op_name[50];
	strcpy(op_name, "remove");
	Operation* operation1 = createOperation(m, op_name);
	push(s->undoStack, operation1);
	//Operation* operation2 = createOperation(m, op_name);
	//push(s->redoStack, operation2);
}

void update_medicine_serv(Service* s, char* name, double concentration, int quantity, double price)
{
	Medicine* m = find(get_repo(s), name, concentration);
	if (m == NULL)
	{
		return;
	}
	Medicine* old_med = copy_medicine(m);
	int pos = find_position(get_repo(s), m);
	Medicine* new_med = create_medicine(name, concentration, quantity, price);
	update_medicine(get_repo(s), pos, new_med);
	char op_name[50];
	strcpy(op_name, "update");
	Operation* undo_op = createOperation(old_med, op_name);
	push(s->undoStack, undo_op);
	Operation* redo_op = createOperation(new_med, op_name);
	push(s->redoStack, redo_op);
}

Repository* get_repo(Service* s)
{
	return s->repo;
}
int compare(const void* a, const void* b)
{
	Medicine* med1 = *(Medicine**)a;
	Medicine* med2 = *(Medicine**)b;
	return strcmp(get_name(med1), get_name(med2));
}
DynamicArray* search_medicines_by_name(Service* s, const char* string)
{
	if (s == NULL || string == NULL)
		return NULL;
	if (get_repo(s) == NULL)
		return NULL;

	DynamicArray* result = createDynamicArray(10, (destroyFunction)destroy_medicine);
	if (result == NULL)
		return NULL;

	for (int i = 0; i < get_repo_length(get_repo(s)); i++)
	{
		Medicine* medicine = get_medicine_on_pos(get_repo(s), i);
		if (strstr(get_name(medicine), string) != 0)
		{
			addElemToArray(result, medicine);
		}
	}
	qsort(result->elems, getSize(result), sizeof(Medicine*), compare);
	return result;
	
}


DynamicArray* find_medicines_in_short_supply(Service* s, int threshold)
{
	if (s == NULL || threshold <= 0)
		return NULL;

	if (get_repo(s) == NULL)
		return NULL;

	DynamicArray* result = createDynamicArray(10, (destroyFunction)destroy_medicine);
	if (result == NULL)
		return NULL;

	for (int i = 0; i < get_repo_length(get_repo(s)); i++)
	{
		Medicine* medicine = get_medicine_on_pos(get_repo(s), i);
		if (get_quantity(medicine) < threshold)
			addElemToArray(result, medicine);

	}
	return result;
}

int undo(Service* s)
{
	if (isEmpty(s->undoStack))
	{
		return 0;
	}
	Operation* lastOperation = pop(s->undoStack);

	if (strcmp(getOperationType(lastOperation), "add") == 0)
	{
		Medicine* medicine = getMedicine(lastOperation);
		delete_medicine(get_repo(s), find_position(get_repo(s), medicine));
	}
	else if (strcmp(getOperationType(lastOperation), "remove") == 0)
	{
		Medicine* medicine = getMedicine(lastOperation);
		add_medicine(get_repo(s), medicine);
	}
	else if (strcmp(getOperationType(lastOperation), "update") == 0)
	{	
		Medicine* old_medicine = getMedicine(lastOperation);
		Medicine* new_med = find(get_repo(s), get_name(old_medicine), get_concentration(old_medicine));
		if (new_med != NULL)
		{
			update_medicine(get_repo(s), find_position(get_repo(s), new_med), copy_medicine(old_medicine));

		}

	}
	push(s->redoStack, lastOperation);
	return 1;
}

int redo(Service* s)
{
	if (isEmpty(s->redoStack))
	{
		return 0; 
	}

	Operation* lastOperation = pop(s->redoStack);

	if (strcmp(getOperationType(lastOperation), "add") == 0)
	{
		Medicine* medicine = getMedicine(lastOperation);
		add_medicine(get_repo(s), medicine); 
	}
	else if (strcmp(getOperationType(lastOperation), "remove") == 0)
	{
		Medicine* medicine = getMedicine(lastOperation);
		delete_medicine(get_repo(s), find_position(get_repo(s), medicine)); 
	}
	else if (strcmp(getOperationType(lastOperation), "update") == 0)
	{
		Medicine* new_medicine = getMedicine(lastOperation);
		Medicine* old_medicine = find(get_repo(s), get_name(new_medicine), get_concentration(new_medicine)); // Find the previous state
		if (old_medicine != NULL)
		{
			update_medicine(get_repo(s), find_position(get_repo(s), old_medicine), copy_medicine(new_medicine)); // Redo update operation
		}
	}

	push(s->undoStack, lastOperation);
	return 1; 
}

void test_service()
{
	Repository* r = create_repository();
	OperationsStack* undos = createStack();
	OperationsStack* redos = createStack();
	Service* s = create_service(r, undos,redos);
	char name[50];
	//test add medicine serv
	strcpy(name, "Aspacardin");
	assert(add_medicine_serv(s, name, 3, 6, 2)==1);
	assert(get_repo_length(get_repo(s)) == 1);
	//test update medicine
	update_medicine_serv(s, name, 3, 4, 8);
	assert(get_quantity(find(r, name, 3)) == 4);
	//test search medicines by name
	char string[50];
	strcpy(string, "card");
	DynamicArray* arr1 = search_medicines_by_name(s, string);
	assert(getSize(arr1) == 1);
	strcpy(string, "ww");
	DynamicArray* arr2 = search_medicines_by_name(s, string);
	assert(getSize(arr2) == 0);
	//test remove medicine serv
	remove_medicine_serv(s, name, 3);
	assert(get_repo_length(get_repo(s)) == 0);

	//Test undo and redo
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	assert(undoStack != NULL && redoStack != NULL);

	add_medicine_serv(s, name, 1, 10, 5);
	int undoResult = undo(s);
	assert(undoResult == 1);

	int redoResult = redo(s);
	assert(redoResult == 1);
	assert(get_repo_length(get_repo(s)) == 1);

	Medicine* medicine1AfterRedo = find(s->repo, name, 1);
	assert(medicine1AfterRedo != NULL);

}