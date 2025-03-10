#pragma once
#include "Tutorial.h"
#include <vector>
class WatchList
{
protected:

	vector <Tutorial> watch_list;
	const string fileName;
public:
	WatchList(const string fileName) : fileName{ fileName } {};
	virtual ~WatchList() {};
	void add_to_watchlist(Tutorial& t);
	void remove_from_watchlist(string title);
	void play_tutorial(Tutorial& t);
	vector<Tutorial> get_watchlist();
	virtual void write_to_file() const = 0;
	virtual void open_in_app()const =0;
	const string get_fileName()const { return this->fileName; }
};


class CSVWatchList : public WatchList
{
public:
	~CSVWatchList() {};
	CSVWatchList(const string FileName) : WatchList{ fileName } {};
	void write_to_file() const override;
	void open_in_app()const override;
};

class HTMLWatchList : public WatchList
{
public:
	~HTMLWatchList() {};
	HTMLWatchList(const string FileName) : WatchList{ fileName } {};
	void write_to_file() const override;
	void open_in_app()const override;
};
 
