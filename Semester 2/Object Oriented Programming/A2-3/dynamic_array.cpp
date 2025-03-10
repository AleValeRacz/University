#include "dynamic_array.h"
#include <stdlib.h>
#include<assert.h>
DynamicArray* createDynamicArray(int capacity, destroyFunction op)
{
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr == NULL)
        return NULL;
    arr->capacity = capacity;
    arr->size = 0;
    arr->elems = (TElem*)malloc(sizeof(TElem) * capacity);
    if (arr->elems == NULL)
    {
        free(arr);
        return NULL;
    }
    arr->destroyOp = op;
    return arr;
}

void destroyDynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; i < arr->size; i++)
        arr->destroyOp(arr->elems[i]);

    free(arr->elems);
    free(arr);
}

void resize(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    arr->capacity *= 2;
    TElem* aux = (TElem*)realloc(arr->elems, sizeof(TElem) * arr->capacity);
    if (aux == NULL)
        return;
    arr->elems = aux;
}

void addElemToArray(DynamicArray* arr, TElem elem)
{
    if (arr == NULL)
        return;
    if (arr->size == arr->capacity)
        resize(arr);
    arr->elems[arr->size++] = elem;
}
void update_element_on_position(DynamicArray* arr, int pos, TElem elem)
{

    arr->elems[pos] = elem;
}
int getSize(DynamicArray* arr)
{
    if (arr == NULL)
        return 0;
    return arr->size;
}

TElem get(DynamicArray* arr, int pos)
{
    if (arr == NULL)
        return NULL;
    if (pos < 0 || pos >= arr->size)
        return NULL;
    return arr->elems[pos];
}

void deleteElemFromArray(DynamicArray* arr, int pos)
{
    if (arr == NULL)
        return;
    if (pos < 0 || pos >= arr->size)
        return;
   // arr->destroyOp(arr->elems[pos]);
    for (int i = pos; i < arr->size - 1; i++)
        arr->elems[i] = arr->elems[i + 1];
    arr->size--;

}
void destroyInt(void* element)
{
    free(element);
}
void Test_dynamic_array()
{
    // Test create array
    DynamicArray* arr = createDynamicArray(2, destroyInt);
    assert(arr != NULL);

    // Test add elemets
    int* elem1 = (int*)malloc(sizeof(int));
    *elem1 = 10;
    addElemToArray(arr, elem1);
    int* elem2 = (int*)malloc(sizeof(int));
    *elem2 = 20;
    addElemToArray(arr, elem2);

    // Test get size function
    assert(getSize(arr) == 2);

    // Test get function
    assert(*(int*)get(arr, 0) == 10);
    assert(*(int*)get(arr, 1) == 20);

    // Test update_element_on_position function
    int newValue = 30;
    update_element_on_position(arr, 0, &newValue);
    assert(*(int*)get(arr, 0) == 30);

    // Test deleteElemFromArray function
    deleteElemFromArray(arr, 0);
    assert(getSize(arr) == 1);
    assert(*(int*)get(arr, 0) == 20);

    // Destroy the dynamic array
    destroyDynamicArray(arr);
}

