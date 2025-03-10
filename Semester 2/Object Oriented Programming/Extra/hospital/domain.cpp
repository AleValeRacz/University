#include "domain.h"
bool NeonatalUnit::isEficient()const
{
	return this->averageGrade > 8.5 && this->nrOfNewborns >= this->nrOfMothers;
}

string NeonatalUnit::toString()const
{
	stringstream buffer;
	buffer << "Neonatal " << this->name << " " << this->nrOfDoctors << " " << this->nrOfMothers << " " << this->nrOfNewborns << " " << "is eficient: " << this->isEficient() << endl;
	return buffer.str();
}

bool Surgery::isEficient()const
{
	return this->nrOfPatients / this->nrOfDoctors >= 2;
}

string Surgery::toString()const
{
	stringstream buffer;
	buffer << "Surgery " << this->name << " " <<  this->nrOfDoctors << " " << this->nrOfPatients << " " << "is eficient: " << this->isEficient() << endl;
	return buffer.str();
}