#pragma once
#include "Task.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository
{
private:
	vector <Task> tasks;
public:
	Repository() { this->load_file(); }
	~Repository() {};
	vector <Task>get_tasks() { return tasks; }
	void load_file();
};

