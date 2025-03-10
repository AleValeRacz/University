#include "ui.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
Ui::Ui()
{

}

Ui:: ~Ui()
{

}

void Ui::print_admin_menu()
{
	cout << endl;
	cout << "Menu" << endl;
	cout << "1.Add tutorial" << endl;
	cout << "2.Remove tutorial" << endl;
	cout << "3.Update tutorial" << endl;
	cout << "4.Print tutorials" << endl;
	cout << "0.Exit" << endl;

}

void Ui::print_main_menu()
{
	cout << endl;
	cout << "Do you wish to use the app as an admin or as a user?" << endl;
	cout << "1.Admin" << endl << "2.User" << endl << "3.Exit"<<endl;

}

void Ui::print_user_menu()
{
	cout << endl;
	cout << "1.See tutorials with a given presenter." << endl;
	cout << "2.Delete a tutorial from the watch list." << endl;
	cout << "3.See the watch list." << endl;
	cout << "0.Exit" << endl;



}
void Ui::add_tutorial_ui()
{
	string title, presenter, link;
	int likes;
	pair<int, int> duration;

	cout << "Enter title: ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter presenter: ";
	cin >> ws;
	getline(cin, presenter);
	cout << "Enter duration (in minutes and seconds): ";
	cin >> duration.first >> duration.second;
	if (cin.fail())
	{
		cout << "Invalid input!";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	
	cout << "Enter nr of likes: ";
	cin >> likes;
	if (cin.fail())
	{
		cout << "Invalid input!";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cout << "Enter link: ";
	cin >> link; 
	Tutorial tutorial = Tutorial(title, presenter, duration, likes, link);
	if (this->service.validate_tutorial(tutorial))
	{
		try {
			this->service.add_tutorial(tutorial);
			cout << "Added succesfully" << endl;
		}
		catch (exception& e)
		{
			cout << "Tutorial with this name already in the repo!" << endl;
		}
	}
	else
		cout << "Invalid input data!<<"<<endl;
	

	
}

void Ui::print_tutorials()
{
	DynamicVector<Tutorial> tutorials = this->service.get_tutorials();
	for (int i = 0; i < tutorials.get_size(); i++)
		cout << "Title: " << tutorials[i].get_title() << "; Presenter: " << tutorials[i].get_presenter() << "; Duration: " << tutorials[i].get_minutes() << " minutes " << tutorials[i].get_seconds() << " seconds; " << "Likes: " << tutorials[i].get_likes() << "; Link: " << tutorials[i].get_link() << endl;
}

void Ui::remove_tutorial_ui()
{
	string title;
	cout << "Enter title for the movie you want to remove: ";
	cin >> ws;
	getline(cin, title);
	try {
		this->service.remove_tutorial(title);
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	

}

void Ui::update_tutorial_ui()
{
	string title, presenter, link;
	int likes;
	pair<int, int> duration;
	cout << "Enter title for the movie you want to update: ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter new presenter: ";
	cin >> ws;
	getline(cin, presenter);
	cout << "Enter new duration (in minutes and seconds): ";
	cin >> duration.first >> duration.second;
	cout << "Enter new nr of likes: ";
	cin >> likes;
	cout << "Enter new link: ";
	cin >> link;
	try
	{
		this->service.update_tutorial(title, presenter, duration.first, duration.second, likes, link);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}
	
void Ui::option1user()
{
	string presenter;
	cin.ignore();
	cout << "Enter the presenter you want to search by: ";
	getline(cin, presenter);
	DynamicVector<Tutorial> tutorials;
	if (presenter == "0")
	{
		tutorials = service.get_tutorials();
	}
	else
	{
		tutorials = this->service.filter_by_presenter(presenter);
		if (tutorials.get_size() == 0)
		{
			cout << "There are no tutorials with this presenter!"<<endl;
			return;
		}

	}
	int i = 0;
	while (tutorials.get_size() != 0)
	{
		if (i == tutorials.get_size())
			i = 0;
		cout << "Title: " << tutorials[i].get_title() << "; Presenter: " << tutorials[i].get_presenter() << "; Duration: " << tutorials[i].get_minutes() << " minutes " << tutorials[i].get_seconds() << " seconds; " << "Likes: " << tutorials[i].get_likes() << "; Link: " << tutorials[i].get_link() << endl;
		this->service.play_tutorial(tutorials[i]);
		cout << "Do you want to add it to the watch list?(yes/no)" << endl;
		string answer;
		cin >> answer;
		if (answer == "yes")
		{
			this->service.add_to_watchlist(tutorials[i]);
			return;
		}
		cout << "Do you wish to continue?(yes/no)" << endl;
		cin >> answer;
		if (answer == "yes")
		{
			i++;
		}
		else
			break;
				
	}
	
}

void Ui::option2user()
{
	string name;
	cout << "Enter tutorial title to remove from watchlist: ";
	cin.ignore();
	getline(cin, name);
	try
	{
		this->service.remove_from_watchlist(name);
		cout << "Removed succesfully!" << endl;
		cout << "Would you like to give it a like?(yes/no)"<<endl<<"answer: ";
		string answer;
		cin >> answer;
		if (answer == "yes")
		{
		this->service.like_tutorial(name);
		}

	}
		
	catch (exception& e)
	{
		cout << "No tutorial with that name in the watch list!"<<endl;
	}

}

void Ui::option3user()
{
	DynamicVector<Tutorial> tutorials = this->service.get_watchlist();
	for (int i = 0; i < tutorials.get_size(); i++)
		cout << "Title: " << tutorials[i].get_title() << "; Presenter: " << tutorials[i].get_presenter() << "; Duration: " << tutorials[i].get_minutes() << " minutes " << tutorials[i].get_seconds() << " seconds; " << "Likes: " << tutorials[i].get_likes() << "; Link: " << tutorials[i].get_link() << endl;
}

void Ui:: run()
{
	this->print_main_menu();
	string option;
	cout << "Enter option: ";
	cin >> option;
	if (option == "1")
	{
		while (true)
		{
			string choice = "0";
			this->print_admin_menu();
			cout << "Enter choice: ";
			cin >> choice;
			if (choice == "1")
				this->add_tutorial_ui();
			else if (choice == "2")
				this->remove_tutorial_ui();
			else if (choice == "3")
				this->update_tutorial_ui();
			else if (choice == "4")
				this->print_tutorials();
			else if (choice == "0")
				break;
			else
				cout << "Invalid choice!";



		}

	}
	else if (option == "2")
	{
		while (true)
		{
			this->print_user_menu();
			string choice = "0";
			cout << "Enter choice: ";
			cin >> choice;
			if (choice == "1")
				this->option1user();

			else if (choice == "2")
				this->option2user();

			else if (choice == "3")
				this->option3user();

			else if (choice == "0")
				break;
			else
				cout << "Invalid input!" << endl;

		}

	}
	else if (option == "3")
		return;
	else
		cout << "Invalid input!" << endl;


			
}