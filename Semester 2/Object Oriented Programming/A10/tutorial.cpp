#include "tutorial.h"
#include <iostream>
#include <sstream>
Tutorial::Tutorial(const string& title,const string& presenter, pair<int, int> duration, int likes,const string& link) : title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link }
{
}

Tutorial::Tutorial(const Tutorial& t)
{
	this->title = t.title;
	this->presenter = t.presenter;
	this->duration = t.duration;
	this->likes = t.likes;
	this->link = t.link;
}

Tutorial::~Tutorial()
{
}

void Tutorial::set_title(string new_title)
{
	this->title = new_title;

}

void Tutorial::set_presenter(string new_presenter)
{
	this->presenter = presenter;
}

void Tutorial::set_minutes(int new_minutes)
{
	this->duration.first = new_minutes;
}
void Tutorial::set_seconds(int new_seconds)
{
	this->duration.second = new_seconds;

}

void Tutorial::set_likes(int new_likes)
{
	this->likes = new_likes;
}
void Tutorial::set_link(string new_link)
{
	this->link = new_link;
}

string Tutorial::to_string() const
{
	stringstream buffer;
	buffer << this->title << "|" << this->presenter << "|" <<this->duration.first << " "<<this->duration.second<<"|" << this->likes << "|" << this->link << endl;
	return buffer.str();
}

ostream& operator<<(ostream& stream, const Tutorial& t)
{
	stream <<quoted(t.title) << " | " << quoted(t.presenter) << " | " << t.duration.first << " " << t.duration.second <<" | "<< t.likes << " | " << quoted(t.link)<<endl;
	return stream;
}

istream& operator>>(istream& stream, Tutorial& t)
{
	string delim;
	stream >> quoted(t.title) >>delim>> quoted(t.presenter)>>delim >> t.duration.first >> t.duration.second >>delim>> t.likes >>delim >> quoted(t.link);
	return stream;
}
