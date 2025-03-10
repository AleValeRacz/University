#include "repository.h"

#include <iostream>

Repository::Repository()
{
	this->create_initial_input();
}
Repository::~Repository()
{

}

void Repository::add_tutorial(const Tutorial& t)
{

	this->tutorials.add(t);
}
void Repository::remove_tutorial(int pos)
{

	this->tutorials.remove(pos);
}
void Repository::update_tutorial(int pos, Tutorial& nt)
{
	this->tutorials.update(pos, nt);
}
DynamicVector <Tutorial> Repository::get_tutorials()
{
	return this->tutorials;
}

int Repository::find_position(string title)
{
	int pos = -1;
	for (int i = 0; i < this->tutorials.get_size(); i++)
		if (this->tutorials.operator[](i).get_title() == title)
			pos = i;
	return pos;

}
Tutorial Repository::get_tutorial_by_title(string title)
{
	for (int i = 0; i < this->tutorials.get_size(); i++)
		if (this->tutorials.operator[](i).get_title() == title)
			return tutorials[i];
	throw exception("Not found!\n");
}

void Repository:: create_initial_input()
{
	Tutorial t = Tutorial("C++ 101", "Procoder", make_pair(54, 12), 1466, "https://www.youtube.com/watch?v=7TJ7Z1-V_24&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on&index=5");
	this->tutorials.add(t);
	 t = Tutorial("Introduction to C++", "alexZ", make_pair(45, 30), 230, "https://www.youtube.com/watch?v=MNeX4EGtR5Y");
	 this->tutorials.add(t);
	 
	 t = Tutorial("OOP in C++", "CodeNinja", make_pair(12, 49), 390, "https://www.youtube.com/watch?v=wN0x9eZLix4");
	 this->tutorials.add(t);
	 t = Tutorial("Become a C++ expert!", "C++Wizard", make_pair(95, 17), 1320, "https://www.youtube.com/watch?v=S3nx34WFXjI&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on");
	 this->tutorials.add(t);
	 t = Tutorial("Advanced C++ Techniques", "C++Wizard", make_pair(32, 0), 72, "https://www.youtube.com/watch?v=4psGUiKacPQ&list=PLZPZq0r_RZOMHoXIcxze_lP97j2Ase2on&index=2");
	 this->tutorials.add(t);
	 t = Tutorial("C++", "STL Guru", make_pair(50, 45), 280, "https://www.youtube.com/watch?v=-QxI-RP6-HM");
	 this->tutorials.add(t);
	 t = Tutorial("Memory Management in C++", "MemoryMaster", make_pair(12, 14), 891, "https://www.youtube.com/watch?v=i_wDa2AS_8w");
	 this->tutorials.add(t);
	 t = Tutorial("C++ tricks", "boredPerfectionist", make_pair(50, 45), 9280, "https://www.youtube.com/watch?v=N6dOwBde7-M");
	 this->tutorials.add(t);
	 t = Tutorial("Get rich with c++", "alphamale", make_pair(84, 56), 3009, "https://www.youtube.com/watch?v=VfaAYvZhD78");
	 this->tutorials.add(t);
	 t = Tutorial("C++ level 7", "abacus154", make_pair(45, 30), 230, "https://www.youtube.com/watch?v=2ybLD6_2gKM");
	 this->tutorials.add(t);
}