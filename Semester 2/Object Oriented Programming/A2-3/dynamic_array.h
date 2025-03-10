#pragma once
#include "domain.h"

typedef void* TElem;
typedef void(*destroyFunction)(TElem);

typedef struct
{
	int size, capacity;
	TElem* elems;
	destroyFunction destroyOp;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity, destroyFunction op);
void destroyDynamicArray(DynamicArray* arr);
void addElemToArray(DynamicArray* arr, TElem elem);
int getSize(DynamicArray* arr);
void deleteElemFromArray(DynamicArray* arr, int pos);
TElem get(DynamicArray* arr, int pos);
void update_element_on_position(DynamicArray* arr, int pos, TElem elem);
void Test_dynamic_array();