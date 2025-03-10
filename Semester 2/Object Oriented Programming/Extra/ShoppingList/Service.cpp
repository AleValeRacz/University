#include "Service.h"


vector <Item> Service::getItemsSorted()
{
	vector<Item> items= this->repo.getItems();
	auto comparator = [](Item& a, Item& b)
		{
			if (a.getCategory() == b.getCategory())
				return a.getName() < b.getName();
			return a.getCategory() < b.getCategory();
		};
	sort(items.begin(), items.end(), comparator);
	return  items;
}

vector <Item> Service::FilterByCategory(string category)
{
	vector <Item> filtered;
	for (auto i : this->getItemsSorted())
		if (i.getCategory() == category)
			filtered.push_back(i);
	auto comparator = [](Item& a, Item& b)
		{
			return a.getQuantity() < b.getQuantity();
		};
	sort(filtered.begin(), filtered.end(), comparator);
	return filtered;
}

vector <Item> Service::SearchNameCategory(string text)
{
	vector <Item> result;
	for (auto i : this->getItemsSorted())
		if (i.getName().find(text) != string::npos || i.getCategory().find(text) != string::npos)
			result.push_back(i);
	return result;

}
