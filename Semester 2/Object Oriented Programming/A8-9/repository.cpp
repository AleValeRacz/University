#include "repository.h"
#include<algorithm>
#include <iostream>

Repository::Repository()
{
	//this->create_initial_input();
	this->read_tutorials("tutorials.txt");
	//this->write_tutorials("tutorials.txt");
}
Repository::~Repository()
{

}

void Repository::add_tutorial(const Tutorial& t)
{

	this->tutorials.push_back(t);
	this->write_tutorials("tutorials.txt");
}
void Repository::remove_tutorial(int pos)
{
	if (pos >= 0 && pos < this->tutorials.size())
	{
		this->tutorials.erase(pos + this->tutorials.begin());
		this->write_tutorials("tutorials.txt");
	}
	else
		throw Exception("The specified tutorial is not in the repo!");
}
void Repository::update_tutorial(int pos, const Tutorial& nt)
{
	if (pos >= 0 && pos < this->tutorials.size())
	{
		this->tutorials[pos] = nt;
		this->write_tutorials("tutorials.txt");
	}
	else
		throw Exception("The specified tutorial is not in the repo!");

}
const vector <Tutorial> Repository::get_tutorials()const
{
	return this->tutorials;
}

int Repository::find_position(string title)
{
	int pos = -1;
	auto it = find_if(this->tutorials.begin(), this->tutorials.end(), [title](const Tutorial& t)
		{
			return t.get_title() == title;
		});
	if (it != this->tutorials.end())
	{
		pos = distance(this->tutorials.begin(), it);
	}
	return pos;

}

void Repository::write_tutorials(const string& file_name)
{
	ofstream fout(file_name);
	for_each(this->tutorials.begin(), this-> tutorials.end(), [&fout](const Tutorial& t)
		{
			fout << t;
		});

}

void Repository::read_tutorials(const string& file_name)
{
	ifstream fin(file_name);
	if (!fin.is_open())
	{
		cout << "no file!\n";
		return;
	}
	Tutorial tutorial;
	while (fin >> tutorial) 
	{
		this->tutorials.push_back(tutorial);
	}
	fin.close();
}


void Repository:: create_initial_input()
{
	Tutorial t = Tutorial("C++ 101", "Procoder", make_pair(54, 12), 1466, "https://www.youtube.com/watch?v=7TJ7Z1-V_24&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on&index=5");
	this->tutorials.push_back(t);
	 t = Tutorial("Introduction to C++", "alexZ", make_pair(45, 30), 230, "https://www.youtube.com/watch?v=MNeX4EGtR5Y");
	 this->tutorials.push_back(t);
	 
	 t = Tutorial("OOP in C++", "CodeNinja", make_pair(12, 49), 390, "https://www.youtube.com/watch?v=wN0x9eZLix4");
	 this->tutorials.push_back(t);
	 t = Tutorial("Become a C++ expert!", "C++Wizard", make_pair(95, 17), 1320, "https://www.youtube.com/watch?v=S3nx34WFXjI&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on");
	 this->tutorials.push_back(t);
	 t = Tutorial("Advanced C++ Techniques", "C++Wizard", make_pair(32, 0), 72, "https://www.youtube.com/watch?v=4psGUiKacPQ&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on&index=2");
	 this->tutorials.push_back(t);
	 t = Tutorial("C++", "STL Guru", make_pair(50, 45), 280, "https://www.youtube.com/watch?v=-QxI-RP6-HM");
	 this->tutorials.push_back(t);
	 t = Tutorial("Memory Management in C++", "MemoryMaster", make_pair(12, 14), 891, "https://www.youtube.com/watch?v=i_wDa2AS_8w");
	 this->tutorials.push_back(t);
	 t = Tutorial("C++ tricks", "boredPerfectionist", make_pair(50, 45), 9280, "https://www.youtube.com/watch?v=N6dOwBde7-M");
	 this->tutorials.push_back(t);
	 t = Tutorial("Get rich with c++", "alphamale", make_pair(84, 56), 3009, "https://www.youtube.com/watch?v=VfaAYvZhD78");
	 this->tutorials.push_back(t);
	 t = Tutorial("C++ level 7", "abacus154", make_pair(45, 30), 230, "https://www.youtube.com/watch?v=2ybLD6_2gKM");
	 this->tutorials.push_back(t);
}