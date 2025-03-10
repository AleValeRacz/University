#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class HospitalDepartment
{
protected:
	string name;
	int nrOfDoctors;
public:
	HospitalDepartment(string name, int nrOfDoctors): name{name}, nrOfDoctors {nrOfDoctors}{}
	virtual ~HospitalDepartment() {};
	virtual bool isEficient() const = 0;
	virtual string toString()const = 0;
	string get_name() { return name; }
	int get_nr_docs() { return nrOfDoctors; }
};

class NeonatalUnit : public HospitalDepartment
{
private:
	int nrOfMothers, nrOfNewborns;
	double averageGrade;
public:
	NeonatalUnit(string name, int nrOfDoctors, int nrOfMothers, int nrOfNewborns, double averageGrade) :HospitalDepartment{ name, nrOfDoctors }, nrOfMothers{ nrOfMothers }, nrOfNewborns{ nrOfNewborns }, averageGrade{ averageGrade } {}
	~NeonatalUnit() {};
	bool isEficient() const override;
	string toString()const override;
	int get_nr_mothers() { return nrOfMothers; }
	int get_nr_newborns() { return nrOfNewborns; }
	int get_averageGrade() { return averageGrade; }
	
};


class Surgery : public HospitalDepartment
{
private:
	int nrOfPatients;
public:
	~Surgery() {};
	Surgery(string name, int nrOfDoctors, int nrOfPatients) :HospitalDepartment{ name, nrOfDoctors }, nrOfPatients {nrOfPatients}{}
	bool isEficient()const override;
	string toString()const override;
	int get_nr_patients() { return nrOfPatients; }

};





