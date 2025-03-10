#include "service.h"
#include <iostream>
#include <string>
#include <cstdlib>

Service::Service()
{
	
}
Service:: ~Service()
{

}

void Service::add_tutorial(Tutorial t)
{
	if (this->repo.find_position(t.get_title()) != -1)
		throw std::exception("Tutorial with this name already in the repo!");
	this->repo.add_tutorial(t);
}

void Service::remove_tutorial(string title)
{

	int pos = this->repo.find_position(title);
	this->repo.remove_tutorial(pos);
}
void Service::update_tutorial(string title, string new_presenter, int new_min, int new_sec, int new_likes, string new_link)
{
	int pos = this->repo.find_position(title);
	Tutorial new_tutorial = Tutorial(title, new_presenter, make_pair(new_min, new_sec), new_likes, new_link);
	if(this->validate_tutorial(new_tutorial))
		this->repo.update_tutorial(pos, new_tutorial);
}

DynamicVector<Tutorial> Service::get_tutorials()
{
	return this->repo.get_tutorials();
}

bool Service:: validate_tutorial(Tutorial& t)
{
	if(t.get_title().empty() || t.get_presenter().empty()|| t.get_link().empty())
			return false;
	if (t.get_minutes() < 0 || t.get_seconds() < 0 || t.get_seconds() > 59)
		return false;
	if (t.get_likes() < 0) 
		return false;
	return true;
}

DynamicVector<Tutorial> Service::filter_by_presenter(string presenter) 
{
	DynamicVector<Tutorial> filtered_t;
	for (int i = 0; i < this->get_tutorials().get_size(); i++)
		if (this->get_tutorials()[i].get_presenter() == presenter)
			filtered_t.add(get_tutorials()[i]);

	return filtered_t;

}

void Service::add_to_watchlist(Tutorial& tutorial)
{
	this->watch_list.add(tutorial);
}

void Service::remove_from_watchlist(string title)
{
	int pos = -1;
	for (int i = 0; i < this->watch_list.get_size(); i++)
		if (this->watch_list[i].get_title() == title)
			pos = i;
	this->watch_list.remove(pos);

}

void Service::like_tutorial(string title)
{

	Tutorial t = this->repo.get_tutorial_by_title(title);
	int pos = this->repo.find_position(title);
	int likes = t.get_likes() + 1;
	Tutorial new_t(t.get_title(),t.get_presenter(),make_pair(t.get_minutes(), t.get_seconds()),likes, t.get_link());
	this->repo.update_tutorial(pos, new_t);
}
DynamicVector<Tutorial> Service::get_watchlist()
{
	return this->watch_list;
}

void Service::play_tutorial(Tutorial &t)
{
	string command = "start " + t.get_link()+ " > NUL 2>&1";
	system(command.c_str());
}