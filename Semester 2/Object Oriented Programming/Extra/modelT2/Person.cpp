#include "Person.h"
#include <string>
#include <fstream>
Person::Person(string name) : name{name}
{

}
Person::~Person()
{
	for (auto* analysis : analyses) 
	{
		delete analysis;
	}
}

void Person::addAnalysis(MedicalAnalysis* a)
{
	this->analyses.push_back(a);

}
vector<MedicalAnalysis*>Person:: getAllAnalysis()
{
	return this->analyses;
}

vector<MedicalAnalysis*>Person::getAnalysisByMonth(int month)
{
	vector<MedicalAnalysis*> new_v;
	for (int i = 0; i < this->analyses.size(); i++)
	{
		MedicalAnalysis *a = this->analyses[i];
		int month_a = stoi(a->get_date().substr(5, 2));
		if (month == month_a)
			new_v.push_back(a);
	}
	return new_v;
}
bool Person::isIll(int month)
{
	vector<MedicalAnalysis*> as = this->getAnalysisByMonth(month);
	for (int i = 0; i < as.size(); i++)
		if (!as[i]->isResultOK())
			return true;
	return false;
}

vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(string date1, string date2)
{
	vector<MedicalAnalysis*> new_v;
	for (int i = 0; i < this->analyses.size(); i++)
	{
		if (this->analyses[i]->get_date() > date1 and this->analyses[i]->get_date() < date2)
			new_v.push_back(this->analyses[i]);

	}
	return new_v;
}
void Person::writeToFile(string date1, string date2)
{
	ofstream fout("analysis.txt");
	vector<MedicalAnalysis*> new_v = this->getAnalysesBetweenDates(date1, date2);
	for (int i = 0; i < new_v.size(); i++)
	{
		fout << new_v[i]->toString();
	}
}