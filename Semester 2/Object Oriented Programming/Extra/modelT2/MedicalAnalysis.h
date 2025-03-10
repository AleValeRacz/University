#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class MedicalAnalysis
{
protected:
	string date;

public:
	MedicalAnalysis(string date);
	virtual ~MedicalAnalysis();
	virtual bool isResultOK() const { return false; }
	virtual string toString()const;
	string get_date() { return this->date; }
};

class BMI : public MedicalAnalysis
{
private:
	double value;

public:
	BMI(string date, double value);
	~BMI();
	double get_value() const { return this->value; }
	string toString()const override;
	bool isResultOK() const  override;
	//friend ofstream& operator<<(ostream& stream, BMI& a);

};

class BP : public MedicalAnalysis
{
private: 
	int s_value;
	int d_value;

public:
	BP(string date, int s_value, int d_value);
	~BP() {};
	int get_svalue() { return this->s_value; }
	int get_dvalue() { return this->d_value; }
	string toString()const override;
	bool isResultOK() const override;
};

