#pragma once
#include "Repository.h"
#include <algorithm>
class Service

{
private:
	Repository repo;
public:
	Service() {};
	~Service() {};
	vector <Bill> get_sorted_bills();
	double calculate_total(string company);

	
};

