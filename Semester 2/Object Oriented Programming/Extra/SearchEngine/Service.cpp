#include "Service.h"

vector <Document> Service::getDocumentsSorted()
{
	vector <Document> documents = this->repo.get_documents();
	auto comparator = [](Document& a, Document& b)
		{
			return a.get_name() < b.get_name();
		};
	sort(documents.begin(), documents.end(), comparator);
	return documents;

}

string Service::bestMatch(string text)
{
	double max_similarity = 0;
	string max_name;
	for (auto d : this->repo.get_documents())
	{
		double similarity;
		if (d.get_name().find(text) != string::npos)
		{
			similarity = static_cast<double>(text.length()) / static_cast<double> (d.get_name().length());
			if (similarity > max_similarity)
			{
				max_similarity = similarity;
				max_name = d.get_name();
			}
		}	
	}
	return max_name;
}

vector<Document> Service::search(string text)
{
	vector<Document>  documents;
	for (auto d : this->repo.get_documents())
	{
		if (d.get_name().find(text) != string::npos)
			documents.push_back(d);
	}
	return documents;

	
}