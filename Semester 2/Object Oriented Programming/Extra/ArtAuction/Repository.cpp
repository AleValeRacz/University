#include "Repository.h"

void Repository::loadRepo()
{
	ifstream input("users.txt");
	string line, name, ids, type;
	while (getline(input, line))
	{
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, ids, '|');
		getline(iss, type, '|');
		int id = stoi(ids);
		this->users.push_back(User(name, id, type));
	}
	input.close();
	input = ifstream("items.txt");
	string category, prices;
	while (getline(input, line))
	{
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, category, '|');
		getline(iss, prices, '|');
		int price = stoi(prices);
		Item item(name, category, price);

		string offer, user_ids, date, sums;
		while (getline(iss, offer, '|'))
		{
			istringstream isso(offer);
			getline(isso, user_ids, ',');
			getline(isso, date, ',');
			getline(isso, sums, '|');
			item.addOffer(stoi(user_ids), stoi(sums), date);
		}
		
		this->items.push_back(item);
	}
}

Repository::~Repository()
{
	ofstream output("items.txt");
	for (auto item : this->items)
	{
		output << item.getName() << "|" << item.getCategory() << "|" << item.getPrice() << "|";
		for (auto offer : item.getOffers())
			output << offer.id << "," << offer.date << "," << offer.sum << "|";
		output << endl;
	}
}

void Repository::addItem(string name, string category, int price)
{
	if (name.empty())
		throw exception("Empty name!");
	if (price <= 0)
		throw exception("Negative price!");
	this->items.push_back(Item(name, category, price));

}
