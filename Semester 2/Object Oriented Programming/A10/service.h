#pragma once
#include <iostream>
#include <string>
#include "repository.h"
#include <algorithm>
#include "Validator.h"
#include "WatchList.h"
#include <UndoRedo.h>
#include <stack>
class Service
{
private:
	Repository repo;
	Validator validator;
	WatchList* watchlist;
	stack <Action*> undoStack;
	stack<Action*> redoStack;



public:
	Service();
	~Service();
	void add_tutorial(Tutorial t);
	void remove_tutorial(string title);
	void update_tutorial(string title, string new_presenter, int new_min, int new_sec, int new_likes, string new_link);
	vector<Tutorial>get_tutorials();
	 vector<Tutorial> filter_by_presenter(string presenter);
	void add_to_watchlist(Tutorial &t);
	void remove_from_watchlist(string title);
	void like_tutorial(string title);
	vector<Tutorial> get_watchlist();
	void play_tutorial(Tutorial &t);
	void dislay_watchlist();
	void set_type_watchlist(WatchList* watchlist);
	void clearFile(string& fileName);

	void undo();
	void redo();
};

