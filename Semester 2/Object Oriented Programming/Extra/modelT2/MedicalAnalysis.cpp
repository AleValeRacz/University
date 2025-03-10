#include "MedicalAnalysis.h"

MedicalAnalysis::MedicalAnalysis(string date) : date{ date }
{

}

MedicalAnalysis::~MedicalAnalysis()
{

}
string MedicalAnalysis::toString()const
{
	stringstream buffer;
	buffer << "Medical analysis: " << this->date << endl;
	return buffer.str();

}

BMI::BMI(string date, double value) : MedicalAnalysis{date}, value {value}
{

}

BMI::~BMI()
{

}

string BMI::toString()const
{
	stringstream buffer;
	buffer << "BMI: " << this->date << " " << this->value <<" "<<this->isResultOK()<< endl;
	return buffer.str();
}
bool BMI::isResultOK()const
{
	return value >= 18.5 and value <= 25;
}
/*
ofstream& operator<<(ostream& stream, BMI& a)
{
	stream << a.toString();
}
*/
BP::BP(string date, int s_value, int d_value) :MedicalAnalysis{ date }, s_value{ s_value }, d_value{ d_value }
{

}
string BP::toString()const
{
	stringstream buffer;
	buffer << "BP: " << this->date << " " << this->s_value << " " << this->d_value << endl;
	return buffer.str();
}
bool BP::isResultOK()const
{
	return this->s_value >= 90 and this->s_value <= 119 and this->d_value >= 60 and this->d_value <= 79;

}
