#pragma once
#include "Observer.h"
#include "Repository.h"
class ItemManager : public Observable
{
private:
	Repository& repo;
public:
	ItemManager(Repository& repo) : repo{ repo } {};
	void addItem(string name, string category, int price);
	void updatePriceOffers(string name, int newPrice, int id, int sum, string date);
	~ItemManager() {};
	vector <Item> getItems() { return this->repo.getItems(); }
	vector <User> getUsers() { return this->repo.getUsers(); }
	Item getItemByName(string name);
};

