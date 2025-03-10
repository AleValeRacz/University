#pragma once
#include <iostream>
#include "tutorial.h"
#include "dynamic_vector.h"

class Repository
{
private:
	DynamicVector <Tutorial> tutorials;

public:

	Repository();
	~Repository();
	void add_tutorial(const Tutorial& t);
	void remove_tutorial(int pos);
	void update_tutorial(int pos,Tutorial& nt);
	DynamicVector <Tutorial> get_tutorials();
	int find_position(string title);
	void create_initial_input();
	Tutorial get_tutorial_by_title(string title);

};

