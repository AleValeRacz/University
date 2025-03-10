#pragma once
#include "Bills.h"
#include <vector>
#include <sstream>
#include <fstream>
class Repository
{
private:
	vector <Bill> bills;
public:
	Repository() { this->read_file(); };
	~Repository() {};
	void read_file();
	vector <Bill> get_bills() { return bills; }

};

