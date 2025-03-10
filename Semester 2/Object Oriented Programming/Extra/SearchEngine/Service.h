#pragma once
#include "Repository.h"
#include <algorithm>
class Service
{
private:
	Repository repo;
public:
	Service() {};
	~Service() {};
	vector <Document> getDocumentsSorted();
	string bestMatch(string text);
	vector <Document> search(string text);
	
};



