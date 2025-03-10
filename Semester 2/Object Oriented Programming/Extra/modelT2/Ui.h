#pragma once
#include "Person.h"
class Ui
{
private:
	Person person = Person("Alex");

public:
	Ui();
	~Ui();
	void start();
	void print_menu();


};

