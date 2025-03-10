#include "domain.h"

string Client::toString()
{
	stringstream buffer;
	buffer << this->name << " " << this->income << endl;
	return buffer.str();
}

bool Person::isInterested(Dwelling* d)const
{
	return d->get_price() / 1000 <= this->income;
}

double Company::totalIncome() {
	return (this->income + this->moneyFromInvestments);
}
string Company::toString()
{
	stringstream buffer;
	buffer << this->name << " " << this->income << " " << this->moneyFromInvestments <<" "<<this->totalIncome()<< endl;
	return buffer.str();
}
bool Company::isInterested(Dwelling* d)const
{
	return (d->get_price() / 1000 <= (this->income + this->moneyFromInvestments));

}
