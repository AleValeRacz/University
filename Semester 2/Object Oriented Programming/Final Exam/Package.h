#pragma once
#include <string>
#include <vector>
using namespace std;

class Package
{
private:
	string recipient;
	pair<string, int> adress;
	pair<double, double> location;
	bool status;
public:
	Package(string recipient, string street, int nr, double x, double y, bool status) : recipient{ recipient }, adress{ street, nr }, location{ x,y }, status{ status } {}
	~Package() {};
	string getRecipient() { return this->recipient; }
	pair<string, int> getAdress(){ return this->adress; }
	pair<double, double> getLocation() { return this->location; }
	bool getStatus() { return this->status; }
	string toString() {
		string str = recipient + "|" + adress.first + "," + to_string(adress.second) + "|" + to_string(location.first) + "," + to_string(location.second) + "|";
		if (status) str += "delivered";
		else str += "not delivered";
		return str + "|\n";
	}

	void setDelivered() { this->status = "delivered"; }

};

