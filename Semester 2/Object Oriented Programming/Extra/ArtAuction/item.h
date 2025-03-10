#pragma once
#include <string>
#include <vector>
using namespace std;

typedef struct offer
{
	int id, sum;
	string date;
}offer;

class Item
{
private:
	
	string name, category;
	int price;
	vector <offer> listOffers;
public:
	Item(string name, string category, int price) : name{ name }, category{ category }, price{ price } {};
	void addOffer(int id, int sum, string date) { this->listOffers.push_back({ id,sum,date }); }
	string getName() { return name; }
	string getCategory() { return category; }
	int getPrice() { return price; }
	vector<offer> getOffers() { return listOffers; }
	~Item() {};
	string toString() { return name+"," + category + "," + to_string(price); }
	void setPrice(int newPrice) { price = newPrice; }
};