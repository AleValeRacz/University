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
	vector <Document> get_documents_sorted();
	vector <Document> search(string text);
	string bestMatch(string text);

};

