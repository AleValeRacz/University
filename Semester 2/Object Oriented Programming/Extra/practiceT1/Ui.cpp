#include "Ui.h"
Ui::Ui()
{

}
Ui::~Ui()
{

}
void Ui::print_menu()
{
	cout << "1.Add." << endl<<"2.Remove"<<endl<<"3.Sort all"<<endl<<"4.Filter"<<endl<<"0.Exit"<<endl;
	
}

void Ui::run()
{
	while (true)
	{
		string choice = "0";
		this->print_menu();
		cout << "Enter choice: ";
		cin >> choice;
		if (choice == "1")
		{
			string model, manuf, color;
			int year;
			cout << "Manufacturer: ";
			cin >> manuf;
			cout << "Model: ";
			cin >> model;
			cout << "year: ";
			cin >> year;
			cout << "Color: ";
			cin >> color;
			int result = this->serv.add_car(manuf, model, year, color);
			if (result == -1)
				cout << "Already in the repo!" << endl;
			else
				cout << "Added succesfully!" << endl;
		}
		else if (choice == "2")
		{
			string model;
			int year;
			cin >> model >> year;
			this->serv.remove_car(model, year);


		}
		else if (choice == "3")
		{
			DynamicVector<Car> cars = this->serv.sort_by_manu_and_model();
			for (int i = 0; i < cars.get_size(); i++)
				cout << cars[i].get_manufacturer() << "|" << cars[i].get_model() << "|" << cars[i].get_year() << "|" << cars[i].get_color() << endl;

		}
		else if (choice == "4")
		{
			DynamicVector<Car> cars = this->serv.sort_by_color();
			for (int i = 0; i < cars.get_size(); i++)
				cout << cars[i].get_manufacturer() << "|" << cars[i].get_model() << "|" << cars[i].get_year() << "|" << cars[i].get_color() << endl;
		}
			
		else if (choice == "0")
			break;
			
		
	}
}
