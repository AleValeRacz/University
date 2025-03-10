#pragma once
#include <iostream>
#include <string>
using namespace std;
class Task
{
private:
	string description;
	int duration, priority;
public:
	Task(string description, int duration, int priority) : description{ description }, duration{ duration }, priority{ priority } {};
	~Task() {};
	int get_priority() { return priority; }
	string get_description() { return description; }
	int get_duration() { return duration; }
	string toString() { return description + to_string(duration) + to_string(priority); }

		
	
};

