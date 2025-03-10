#include "UI.h"

void Ui::print_menu()
{
	cout << "1.add department\n2.show all departments\n3.show all eficient departments\n4.write departments to file\n";

}

void Ui::start()
{
	while (true)
	{
		this->print_menu();
		int choice = 0;
		cout << "enter choice: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "neonatal or surgery? (1/2)\n";
			int ops;
			cin >> ops;
			if (ops == 1)
			{
				string name;
				int nr_docs, nr_mothers, nr_newborns;
				double average_grade;

				cout << "name: ";
				cin >> name;
				cout << "nr doctors:";
				cin >> nr_docs;
				cout << "nr mothers: ";
				cin >> nr_mothers;
				cout << "nr new_borns: ";
				cin >> nr_newborns;
				cout << "average grade: ";
				cin >> average_grade;

				NeonatalUnit* dep = new NeonatalUnit(name, nr_docs, nr_mothers, nr_newborns, average_grade);
				this->serv.addDepartment(dep);
			}
			else if (ops == 2)
			{
				string name;
				int nr_docs, nr_patients;

				cout << "name: ";
				cin >> name;
				cout << "nr doctors:";
				cin >> nr_docs;
				cout << "nr patients: ";
				cin >> nr_patients;
				Surgery* dep = new Surgery(name, nr_docs, nr_patients);
				this->serv.addDepartment(dep);

			}



		}
		else if (choice == 2)
		{
			vector <HospitalDepartment*> deps = this->serv.get_all_departments();
			for (int i = 0; i < deps.size(); i++)
				cout << deps[i]->toString();

		}
		else if (choice == 3)
		{

			vector <HospitalDepartment*> deps = this->serv.get_all_eficient_departments();
			for (int i = 0; i < deps.size(); i++)
				cout << deps[i]->toString();
		}
		else if (choice == 4)
		{
			this->serv.writeToFile("departmentss.txt");
		}
		else if (choice == 0)
			break;
		else
			cout << "Invalid choice!\n";

	}
		

}