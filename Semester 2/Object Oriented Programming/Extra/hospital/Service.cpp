#include "Service.h"


Service::~Service()
{
	for (int i = 0; i < this->departments.size(); i++)
	{
		delete this->departments[i];
	}
}
void Service::addDepartment(HospitalDepartment* d)
{
	this->departments.push_back(d);

}

vector <HospitalDepartment*> Service::get_all_eficient_departments()
{
	vector <HospitalDepartment*> vect;
	for (int i = 0; i < this->departments.size(); i++)
		if (this->departments[i]->isEficient())
			vect.push_back(this->departments[i]);
	return vect;
}

void Service::writeToFile(string name)
{
	ofstream fout(name);

	sort(this->departments.begin(), this->departments.end(), compare_names);

	for (int i = 0; i < this->departments.size(); i++)
		fout << this->departments[i]->toString();
}

bool compare_names(HospitalDepartment* d, HospitalDepartment* c)
{
	return d->get_name() < c->get_name();
}
void Service::initial_input()
{
	NeonatalUnit* n1 = new NeonatalUnit("maria", 20, 10, 8 ,9);
	Surgery* n2 = new Surgery("sf aba", 8, 17);
	Surgery* n3 = new Surgery("aof", 10, 18);
	this->departments.push_back(n1);
	this->departments.push_back(n2);
	this->departments.push_back(n3);
}

