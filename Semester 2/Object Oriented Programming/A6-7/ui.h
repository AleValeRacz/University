#pragma once
#include "Service.h"
class Ui
{
private:
	Service service;
public:
	Ui();
	~Ui();
	void print_admin_menu();
	void print_main_menu();
	void print_user_menu();
	void run();
	void print_tutorials();
	void add_tutorial_ui();
	void remove_tutorial_ui();
	void update_tutorial_ui();
	void option1user();
	void option2user();
	void option3user();
	void display_in_file();
};

