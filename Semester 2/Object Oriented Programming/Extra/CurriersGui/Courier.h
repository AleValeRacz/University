#pragma once
#include <string>
#include <vector>
using namespace std;

typedef struct
{
	double x, y, rad;
}zone;
class Courier
{
private:
	string name;
	zone place;
	vector<string> streets;
public:
	Courier(string  name, double x, double y, double rad) : name{ name }, place{ x,y,rad } {};
	~Courier() {}
	void addStreet(string street) { this->streets.push_back(street); }
	string getName() { return this->name;}
	zone getZone() { return this->place; }
	vector<string>& getStreets() { return this->streets; }
	string toString() {
		string str = name + "|" + to_string(place.x) + " " + to_string(place.y) + " " + to_string(place.rad) + "|";
		for (string st : this->streets) str += st + "|"; return str + "\n";
	}

};
