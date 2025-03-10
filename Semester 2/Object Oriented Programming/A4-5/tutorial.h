#pragma once
#include <iostream>
#include <utility>
#include<string>

using namespace std;
class Tutorial
{
private:
	string title, presenter, link;
	pair<int, int> duration;
	int likes;

public:

	Tutorial(const string &title = "",const string &presenter = "", pair<int, int> duration = make_pair(0, 0), int likes = 0, const string &link = "");
	Tutorial(const Tutorial& t);
	~Tutorial();
	string get_title() const { return title; }
	string get_presenter()const { return presenter; }
	int get_minutes() const { return duration.first; }
	int get_seconds() const { return duration.second; }
	int get_likes() const { return likes; }
	string get_link()const { return link; }
	void set_title(string new_title);
	void set_presenter(string presenter);
	void set_minutes(int minutes);
	void set_seconds(int seconds);
	void set_likes(int likes);
	void set_link(string link);

};

