#pragma once
#include <iostream>
#include <string>
using namespace std;

class Bill
{
private:
	string company, serial_nr;
	double sum;
	bool is_paid;
public:
	Bill(string comp, string nr, double sum, bool is_paid) : company{ comp }, serial_nr{ nr }, sum{ sum }, is_paid{ is_paid } {};
	~Bill() {};
	string get_company()const { return company; }
	string get_serial_nr()const { return serial_nr; }
	double get_sum()const { return sum; }
	bool get_is_paid() const { return is_paid; }
	string toString()const 
	{
		string paid;
		if (!is_paid)
			 paid = "false";
		else
			 paid = "true";
		return company + " " + serial_nr + " " + to_string(sum) + " " + paid + " "; 

	}


};

