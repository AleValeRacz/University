#include "Service.h"
#include "math.h"
#include<algorithm>
void Service::addPackage(string recipient, string street, int nr, double x, double y, bool status)
{
	if (recipient.empty())
		throw exception("no te grabi cumetre!");
	this->repo.AddPackage(recipient, street, nr, x, y, status);


}



vector<Package> Service::filterPackages(Courier& cur)
{
	vector<Package> filtered;
	for (auto pack : this->repo.GetPackage())
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

Package& Service::getPackageByRecipient(string recipient)
{
	for (auto& pack : this->repo.GetPackage())
		if (pack.getRecipient() == recipient)
			return pack;
}

vector<Package>& Service::sortPackages()
{
	vector<Package>& sorted = this->repo.GetPackage();
	sort(sorted.begin(), sorted.end(), [](Package& a, Package& b) { 
		return a.getRecipient() > b.getRecipient();
		});

	return sorted;
}

