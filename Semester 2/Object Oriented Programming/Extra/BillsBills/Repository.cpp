#include "Repository.h"

void Repository::read_file()
{
	ifstream file("bills.txt");
	string line, company, nr, sumStr, paidStr;
	double sum;
	bool is_paid;
	char delim = ';';

	while (getline(file, line))
	{
		istringstream iss(line);
		getline(iss, company, delim);
		getline(iss, nr, delim);
		getline(iss, sumStr, delim);
		getline(iss, paidStr, delim);
		sum = stod(sumStr);
		if (paidStr == " true")
			is_paid = 1;
		else
			is_paid = 0;
		this->bills.push_back(Bill(company, nr, sum, is_paid));

	}

}
