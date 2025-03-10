#pragma once
#include <iostream>
#include "tutorial.h"
#include <vector>
#include<fstream>
#include "Exception.h"
class Repository
{
private:
	vector <Tutorial> tutorials;

public:

	Repository();
	~Repository();
	void add_tutorial(const Tutorial& t);
	void remove_tutorial(int pos);
	void update_tutorial(int pos,const Tutorial& nt);
	const vector <Tutorial> get_tutorials()const;
	int find_position(string title);
	void create_initial_input();
	Tutorial get_tutorial_by_title(string title);
	void read_tutorials(const string& file_name);
	void write_tutorials(const string& file_name);
	
};

