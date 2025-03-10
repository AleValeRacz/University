#pragma once
#include "Repository.h"
#include <algorithm>
class Service

{
private:
	Repository repo;
public:
	vector <Task> get_tasks_sorted();
	Service() {};
	~Service() {};
	
};

