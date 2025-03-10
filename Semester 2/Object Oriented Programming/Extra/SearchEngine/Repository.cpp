#include "Repository.h"


void Repository::load_file()
{
	ifstream file("documents.txt");
	string line, name, keywords, content;
	while (getline(file, line))
	{
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, keywords, '|');
		getline(iss, content, '|');
		this->documents.push_back(Document(name, keywords, content));
	}
}