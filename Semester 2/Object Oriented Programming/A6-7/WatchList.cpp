#include "WatchList.h"
#include "Exception.h"
#include <fstream>
void WatchList::add_to_watchlist(Tutorial& tutorial)
{
	this->watch_list.push_back(tutorial);
}

void WatchList::remove_from_watchlist(string title) {
	auto it = std::find_if(watch_list.begin(), watch_list.end(), [title](const Tutorial& t)
		{
			return t.get_title() == title;
		});

	if (it != watch_list.end()) {
		watch_list.erase(it);
	}
	else {
		throw Exception("Tutorial not found in watch list!\n");
	}
}
vector<Tutorial> WatchList::get_watchlist()
{
	return this->watch_list;
}


void WatchList::play_tutorial(Tutorial& t)
{
	string command = "start " + t.get_link() + " > NUL 2>&1";
	system(command.c_str());
}

void CSVWatchList::open_in_app() const
{
	this->write_to_file();
	string command = "start CSVWatchList.csv";
	system(command.c_str());

}
void HTMLWatchList::open_in_app() const
{

	this->write_to_file();
	string command = "start HTMLWatchList.html";
	system(command.c_str());

}
void CSVWatchList::write_to_file()const
{
	ofstream CSV_out("CSVWatchList.csv");
	if (!CSV_out.is_open())
		throw Exception("The CSV file couldn't be opened!\n");
	CSV_out << "Title,presenter,Minutes & Seconds,Likes,Link\n";
	for (int i = 0; i < this->watch_list.size(); i++)
		CSV_out << this->watch_list[i].get_title() << "," << this->watch_list[i].get_presenter() << "," << this->watch_list[i].get_minutes() << " " << this->watch_list[i].get_seconds() << "," << this->watch_list[i].get_likes() << "," << this->watch_list[i].get_link()<<endl;
	CSV_out.close();
}

void HTMLWatchList::write_to_file()const
{
	ofstream HTML_out("HTMLWatchList.html");
	if (!HTML_out.is_open())
		throw Exception("The HTML file couldn't be opened!\n");
	HTML_out << "<!DOCTYPE html> <html> <head> <title> Tutorial Watch List</title> </head > <body> <table border=\"1\">";
	HTML_out << "<tr> <td> Title </td> <td> Presenter </td> <td> Minutes & seconds </td> <td> Likes </td> < <td> Link </td> </tr>";
	for (int i = 0; i < this->watch_list.size(); i++)
		HTML_out << "<tr> <td>"<< this->watch_list[i].get_title() << "</td> <td>" << this->watch_list[i].get_presenter() << "</td> <td>" << this->watch_list[i].get_minutes() <<" " << this->watch_list[i].get_seconds() << "</td> <td>" << this->watch_list[i].get_likes() << "</td> <td>" << this->watch_list[i].get_link() << "</td> </tr>";
	HTML_out << "</table> </body> </html>";
	HTML_out.close();

}