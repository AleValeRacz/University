#pragma once
#include "domain.h"
#include <vector>
#include <fstream>
#include <algorithm>
class Service
{
private:
	vector <HospitalDepartment*> departments;
public:
	~Service();
	Service() { this->initial_input(); };
	void addDepartment(HospitalDepartment* d);
	vector <HospitalDepartment*> get_all_departments() { return this->departments; }
	vector <HospitalDepartment*> get_all_eficient_departments();
	void initial_input();
	//static bool compare_names(HospitalDepartment* d, HospitalDepartment* c);
	void writeToFile(string file_name);
};

 bool compare_names(HospitalDepartment* d, HospitalDepartment* c);


