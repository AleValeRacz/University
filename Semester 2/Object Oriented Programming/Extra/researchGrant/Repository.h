#pragma once
#include "Researcher.h"
#include "Idea.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
class Repository
{

private:
	vector <Researcher> researchers;
	vector <Idea> ideas;
public:
	vector <Researcher> getResearchers() { return researchers; }
	vector <Idea>& getIdeas();
	Repository() { this->loadFile(); };
	void AddIdea(string title, string description, string status, string creator, int duration);
	~Repository() {};
	void loadFile();
	void saveFile() {};
	bool hasAccepted(Researcher res);
	Idea& getIdeaByTitle(string title);

	
};

