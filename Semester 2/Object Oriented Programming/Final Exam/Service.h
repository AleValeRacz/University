#pragma once
#include "Repository.h"
#include "Observer.h"
class Service: public Observable
{

private:
	Repository& repo;
public:
	Service(Repository &repo): repo{repo} {}
	~Service() {};
	vector<Courier>& getCouriers() { return repo.getCourier(); }
	vector<Package>& getPackages() { return repo.getPackages(); }
	vector<Package> filteredPackages(Courier& cur);
	Package& getPackagaByRecipient( string recipient);
	void addPackage(string recipient, string street, int number, double x, double y, bool status);

};

