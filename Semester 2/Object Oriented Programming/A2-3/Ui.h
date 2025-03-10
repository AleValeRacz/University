#pragma once
#include "services.h"
typedef struct
{
	Service* serv;
}Ui;
Ui* createUi(Service* s);
void destroyUi(Ui* ui);
void start(Ui* ui);