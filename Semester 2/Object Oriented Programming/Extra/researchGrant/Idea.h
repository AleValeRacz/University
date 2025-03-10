#pragma once
#include <string>

using namespace std;
class Idea
{
private:
	string title, description, status, creator;
	int duration;
public:
	Idea(string title, string description, string status, string creator, int duration) : title{ title }, description{ description }, status{ status }, creator{ creator }, duration{ duration } {};
	~Idea() {};
	string getTitle() const { return this->title; }
	string getDescription() const { return this->description; }
	string getStatus() const { return this->status; }
	string getCreator() const { return this->creator; }
	int getDuration() const { return this->duration; }
	string toString() const {return title + " " + description + " " + status + " " + creator + " " + to_string( duration);}
	void setDescription(string val) { this->description = val; }
	void setAccepted() { string val = "accepted"; this->status = val; }
 };

