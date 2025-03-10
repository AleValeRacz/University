#pragma once
#include <iostream>
#include <string>
#include "repository.h"
class Service
{
private:
	Repository repo;
	DynamicVector <Tutorial> watch_list;

public:
	Service();
	~Service();
	void add_tutorial(Tutorial t);
	void remove_tutorial(string title);
	void update_tutorial(string title, string new_presenter, int new_min, int new_sec, int new_likes, string new_link);
	DynamicVector<Tutorial>get_tutorials();
	bool validate_tutorial(Tutorial& t);
	DynamicVector<Tutorial> filter_by_presenter(string presenter);
	void add_to_watchlist(Tutorial &t);
	void remove_from_watchlist(string title);
	void like_tutorial(string title);
	DynamicVector<Tutorial> get_watchlist();
	void play_tutorial(Tutorial &t);
};

