#include "Service.h"
#include "math.h"

vector<Package> Service::filteredPackages(Courier& cur)
{
	vector<Package> filtered;
	for (auto pack : this->repo.getPackages())
	{
		if (sqrt((pack.getLocation().first - cur.getZone().x) * (pack.getLocation().first - cur.getZone().x) + (pack.getLocation().second - cur.getZone().y) * (pack.getLocation().second - cur.getZone().y)) < cur.getZone().rad)
			filtered.push_back(pack);
		else {
			for (auto st : cur.getStreets())
				if (pack.getAdress().first == st)
				{
					filtered.push_back(pack);
					break;
				}
		}
	}
	return filtered;
}

Package& Service::getPackagaByRecipient(string recipient)
{
	for (auto& pack : this->getPackages())
	{
		if (pack.getRecipient() == recipient)
			return pack;
	}
}


void Service::addPackage(string recipient, string street, int number, double x, double y, bool status)
{
	this->repo.addPackage(recipient, street, number, x, y, status);

}


