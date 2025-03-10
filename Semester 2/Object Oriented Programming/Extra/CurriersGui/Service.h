#pragma once
#include "Repository.h"
#include "Observer.h"
class Service :public Observable
{

private:
	Repository& repo;
	vector<msg> messages;
public:
	Service(Repository &repo): repo{repo}{}
	~Service(){}
	vector<Courier>& GetCouriers() { return this->repo.GetCouriers(); }
	vector<Package>& GetPackage() { return this->repo.GetPackage(); }
	void addPackage(string recipient, string street, int nr, double x, double y, bool status);
	vector<Package> filterPackages(Courier& cur);
	Package& getPackageByRecipient(string recipient);
	vector<msg>& getMessages() { return this->messages; }
	void addMessage(msg m) { this->messages.push_back(m); }
	vector<Package>& sortPackages();

};

