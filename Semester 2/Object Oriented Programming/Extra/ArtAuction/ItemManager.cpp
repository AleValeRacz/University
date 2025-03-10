#include "ItemManager.h"
#include <assert.h>

void ItemManager::addItem(string name, string category, int price)
{
	this->repo.addItem(name, category, price);
	this->notify();
}


void ItemManager::updatePriceOffers(string name, int newPrice, int user_id, int sum, string date)
{
	auto& items = this->repo.getItems();
	auto it = find_if(items.begin(), items.end(), [name](Item& item)
		{
			return item.getName() == name;
		});
	if (it != repo.getItems().end()) {
		it->addOffer(user_id, sum, date);
		it->setPrice(sum);
		this->notify();
	}

}

Item ItemManager::getItemByName(string name) {
	for (auto item : this->repo.getItems()) {
		if (item.getName() == name) {
			return item;
		}
	}
	throw exception("no item with this name found!");
}



