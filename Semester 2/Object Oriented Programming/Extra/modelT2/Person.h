#pragma once
#include "MedicalAnalysis.h"
#include <vector>
class Person
{
private:
	string name;
	vector<MedicalAnalysis*> analyses;
public:
	Person(string name);
	~Person();
	void addAnalysis(MedicalAnalysis* a);
	vector<MedicalAnalysis*> getAllAnalysis();
	vector<MedicalAnalysis*> getAnalysisByMonth(int month);
	bool isIll(int month);
	vector<MedicalAnalysis*> getAnalysesBetweenDates(string date1, string date2);
	void writeToFile(string date1, string date2);
};


