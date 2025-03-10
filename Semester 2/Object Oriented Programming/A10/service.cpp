#include "service.h"
#include <iostream>
#include <string>
#include <cstdlib>
Service::Service()
{
	this->watchlist = nullptr;
}
Service:: ~Service()
{ 
	delete this->watchlist;
}

void Service::add_tutorial(Tutorial t)
{
	if (this->repo.find_position(t.get_title()) != -1)
		throw Exception("Tutorial with this name already in the repo!");
	this->validator.validate_tutorial(t);
	this->repo.add_tutorial(t);
	Tutorial* tutorial = new Tutorial{ t.get_title(), t.get_presenter(), {t.get_minutes(), t.get_seconds()}, t.get_likes(), t.get_link() };
	Action* addAction = new ActionAdd(*tutorial, this->repo);
	this->undoStack.push(addAction);
	while (!this->redoStack.empty())
		this->redoStack.pop();
}

void Service::remove_tutorial(string title)
{
	int pos = this->repo.find_position(title);
	Tutorial t = this->repo.get_tutorial_by_title(title);
	Tutorial* tutorial = new Tutorial{ t.get_title(), t.get_presenter(), {t.get_minutes(), t.get_seconds()}, t.get_likes(), t.get_link() };
	this->repo.remove_tutorial(pos);
	Action* removeAction = new ActionRemove(*tutorial, this->repo);
	this->undoStack.push(removeAction);
	while (!this->redoStack.empty())
		this->redoStack.pop();

}
void Service::update_tutorial(string title, string new_presenter, int new_min, int new_sec, int new_likes, string new_link)
{
	int pos = this->repo.find_position(title);
	Tutorial new_tutorial = Tutorial(title, new_presenter, make_pair(new_min, new_sec), new_likes, new_link);
	Tutorial t = this->repo.get_tutorial_by_title(title);
	Tutorial* old_tutorial = new Tutorial{ t.get_title(), t.get_presenter(), {t.get_minutes(), t.get_seconds()}, t.get_likes(), t.get_link() };
	this->validator.validate_tutorial(new_tutorial);
	this->repo.update_tutorial(pos, new_tutorial);


	Tutorial * new_tut =  new Tutorial(title, new_presenter, make_pair(new_min, new_sec), new_likes, new_link);

	Action* updateAction = new ActionUpdate(*old_tutorial, *new_tut, this->repo);
	this->undoStack.push(updateAction);
	while (!this->redoStack.empty())
		this->redoStack.pop();

}


void Service::undo() {
	if (undoStack.empty())
		throw Exception("No more undos!\n");

	Action* action = undoStack.top();
	undoStack.pop();
	action->executeUndo();
	//redoStack.push(move(action));
	redoStack.push(action);
}

void Service::redo() {
	if (redoStack.empty())
		throw Exception("No more redos!\n");
	Action* action = redoStack.top();
	redoStack.pop();
	action->executeRedo();
	//undoStack.push(move(action));
	undoStack.push(action);
}
vector<Tutorial> Service::get_tutorials()
{
	return this->repo.get_tutorials();
}

vector<Tutorial> Service::filter_by_presenter(string presenter) 
{
	vector<Tutorial> tutorials = this->repo.get_tutorials();
	vector<Tutorial> filtered_t;
	copy_if(tutorials.begin(),tutorials.end(), back_inserter(filtered_t), [presenter](const Tutorial& t)
		{
			return t.get_presenter() == presenter;
		});
	return filtered_t;

}



void Service::like_tutorial(string title)
{

	int pos = this->repo.find_position(title);
	Tutorial t = this->get_tutorials()[pos];
	int likes = t.get_likes() + 1;
	Tutorial new_t(t.get_title(),t.get_presenter(),make_pair(t.get_minutes(), t.get_seconds()),likes, t.get_link());
	this->repo.update_tutorial(pos, new_t);
}

void Service::add_to_watchlist(Tutorial& t)
{
	this->watchlist->add_to_watchlist(t);
}
void Service::remove_from_watchlist(string title)
{
	this->watchlist->remove_from_watchlist(title);
}

vector<Tutorial> Service::get_watchlist()
{
	return this->watchlist->get_watchlist();
}
void Service:: play_tutorial(Tutorial& t)
{
	this->watchlist->play_tutorial(t);
}
void Service::dislay_watchlist()
{
	this->watchlist->open_in_app();
}

void Service::set_type_watchlist(WatchList *wl)
{
	this->watchlist = wl;
	
}

void Service::clearFile(string& fileName)
{
	std::ofstream file(fileName);
	file.close();
}
