#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class Dwelling
{
private:
	double price;
	bool isProfitable;
public:
	Dwelling(double price, bool isProfitable): price{price}, isProfitable {isProfitable}{}
	double get_price() { return price; }
};
class Client
{
protected:

	string name;
	double income;
public:
	virtual ~Client() {};
	Client(string name, double income): name{name}, income{income}{}
	virtual double totalIncome() { return income; };
	virtual string toString();
	virtual bool isInterested(Dwelling *d) const = 0;
	string get_name() { return name; }
};

class Person : public Client
{
public:
	Person(string name, double income) : Client{ name,income }{}
	~Person() {};
	bool isInterested(Dwelling *d) const override;
};

class Company : public Client
{
private: 
	double moneyFromInvestments;
public:
	~Company() {};
	Company(string name, double income, double moneyFromInvestments):Client{ name,income }, moneyFromInvestments{moneyFromInvestments}{}
	double totalIncome()override;
	string toString() override;
	bool isInterested(Dwelling *d) const override;
};










