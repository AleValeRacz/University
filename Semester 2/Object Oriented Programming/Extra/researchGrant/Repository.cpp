#include "Repository.h"

vector<Idea> &Repository::getIdeas()
{

	vector<Idea>& sorted = ideas;
	sort(sorted.begin(), sorted.end(), [](Idea& a, Idea& b) {
		return a.getDuration() < b.getDuration();
		});

	return sorted;
}

void Repository::AddIdea(string title, string description, string status, string creator, int duration)
{
	if (title.empty() || duration < 1 || duration > 3)
		throw exception("OY, incorrct data!");
	this->ideas.push_back(Idea(title, description, status, creator, duration));
}


void Repository::loadFile()
{
	ifstream fin("reser.txt");
	string name, position, line;
	while (getline(fin, line))
	{
		istringstream iss(line);
		getline(iss, name, '|');
		getline(iss, position, '|');
		this->researchers.push_back(Researcher(name, position));

	}
	fin.close();

	std::string title, description, status, creator, durations;
	fin = ifstream("ideas.txt");
	while (getline(fin, line))
	{
		istringstream iss(line);
		getline(iss, title, '|');
		getline(iss, description, '|');
		getline(iss, status, '|');
		getline(iss, creator, '|');
		getline(iss, durations, '|');
		this->ideas.push_back(Idea(title, description, status, creator, stoi(durations)));

	}
	fin.close();

	


}

bool Repository::hasAccepted(Researcher res)
{
	for (auto &idea : this->getIdeas())
		if (idea.getCreator() == res.getName())
			if (idea.getStatus() == "accepted")
				return true;
	return false;
}

Idea& Repository::getIdeaByTitle(string title)
{
	for (auto &id : this->ideas)
		if (id.getTitle() == title)
			return id;
}
