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
	vector<string> participants;
public:
	Package(string recipient, string street, int nr, double x, double y, bool status) : recipient{ recipient }, adress{ street,nr }, location{ x,y }, status{ status } {};
	~Package() {};
	string getRecipient() { return recipient; }
	pair<string, int> getAdress() { return adress; }
	pair<double, double> getLocation() { return location; }
	bool getStatus() { return this->status; }
	string toString() {
		string str = recipient + "|" + adress.first + "," + to_string(adress.second) + "|" + to_string(location.first) + "," + to_string(location.second)+"|";
		if (status) str += "delivered";
		else str += "not delivered"; 
		return str + "|\n";

	}
	void setDelivered() { this->status = 1; }
	vector<string> getParticipants() { return this->participants; }
	void addParticipant(string part) { this->participants.push_back(part); }
	void setCoord(double x, double y) { this->location.first = x; this->location.second = y;}

};