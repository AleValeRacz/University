#include "OperationsStack.h"
#include "dynamic_array.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


Operation* createOperation(Medicine* m,  char* operationType)
{
	Operation* o = (Operation*)malloc(sizeof(Operation));
	if (o == NULL)
		return NULL;
	o->medicine = copy_medicine(m);

	if (operationType != NULL)
	{
		o->operationType = (char*)malloc(sizeof(char) * (strlen(operationType) + 1));
		if (o->operationType == NULL)
		{
			free(o);
			return NULL;
		}
		strcpy(o->operationType, operationType);
	}
	else
		o->operationType = NULL;

	return o;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;

	destroy_medicine(o->medicine);
	free(o->operationType);
	free(o);
}

Operation* copyOperation(Operation* o)
{
	if (o == NULL)
		return NULL;
	Operation* copy = createOperation(getMedicine(o), getOperationType(o));
	return copy;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Medicine* getMedicine(Operation* o)
{
	return o->medicine;
}


OperationsStack* createStack()
{
	OperationsStack* s = (OperationsStack*) malloc(sizeof(OperationsStack));
	if (s == NULL)
		return NULL;
	s->stack = createDynamicArray(1000, (destroyFunction)&destroyOperation);
	if (s->stack == NULL)
	{
		free(s);
		return NULL;
	}

	return s;
}

void destroyStack(OperationsStack* s)
{
	if (s == NULL)
		return;
	destroyDynamicArray(s->stack);
	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (s == NULL || o == NULL)
		return;
	addElemToArray(s->stack, o);
}

Operation* pop(OperationsStack* s)
{
	if (s == NULL)
		return NULL;
	int lastPos = getSize(s->stack) - 1;
	Operation* o = (Operation*)get(s->stack, lastPos); 
	Operation* lastOp = copyOperation(o);
	deleteElemFromArray(s->stack, lastPos);
	return lastOp;
}

int isEmpty(OperationsStack* s)
{
	if (s == NULL)
		return 1;
	return (getSize(s->stack) == 0);
}
void clearStack(OperationsStack* s)
{
	if (s == NULL)
		return;
	destroyDynamicArray(s->stack);
	s->stack = createDynamicArray(10, (destroyFunction)& destroyOperation);
	if (s->stack == NULL)
	{
		free(s);
		return;
	}
}
