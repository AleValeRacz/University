#pragma once
#include "Document.h"
#include <vector>
#include <fstream>
#include <sstream>
class Repository
{
private:
	vector <Document> documents;
public:
	Repository() { this->load_file(); }
	~Repository() {};
	vector<Document> get_documents() { return this->documents; }
	void load_file();

};

