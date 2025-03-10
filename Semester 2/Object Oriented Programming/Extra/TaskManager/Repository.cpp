#include "Repository.h"
#include <assert.h>
void Repository::load_file()
{
	ifstream file("taskss.txt");
	string description, durationS, priorityS, line;
	char delim = '|';
	while (getline(file, line))
	{
		istringstream iss(line);
		getline(iss, description, delim);
		getline(iss, durationS, delim);
		getline(iss, priorityS, delim);
		int duration = stoi(durationS);
		int priority = stoi(priorityS);
		this->tasks.push_back(Task(description, duration, priority));

	}
}
