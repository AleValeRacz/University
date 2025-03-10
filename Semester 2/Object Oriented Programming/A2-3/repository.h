#pragma once
#include "dynamic_array.h"

typedef struct
{
	DynamicArray* medicines;
}Repository;

Repository* create_repository();
void destroy_repository(Repository*);
DynamicArray* get_dynamic_array(Repository*);
int add_medicine(Repository*, Medicine*);
void delete_medicine(Repository*, int pos);
void update_medicine(Repository* r, int pos, Medicine* m);
int find_position(Repository* r, Medicine* m);
Medicine* find(Repository* r, char* name, double concentration);
int get_repo_length(Repository* r);
Medicine* get_medicine_on_pos(Repository* r, int pos);
void test_repo();
void initial_input(Repository* r);