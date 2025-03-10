#include "Ui.h"

Ui::Ui()
{

}
Ui::~Ui()
{

}
void Ui::print_menu()
{
	cout << "1.Add analysis\n" << "2.Print Analysis\n" << "3.Show if ill\n" << "4.Save to file\n";
}

void Ui::start()
{
	while (true)
	{
		this->print_menu();
		string option;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1")
		{
			string date;
			int s_value, d_value;
			double value;
			cout << "BMI (1) or BP(2)?\n";
			string op;
			cin >> op;
			if (op == "1")
			{
				cout << "enter date: ";
				cin >> date;
				cout << "enter value: ";
				cin >> value;
				BMI* a = new BMI(date, value);
				this->person.addAnalysis(a);
			}
			else if (op == "2")
			{
				cout << "enter date: ";
				cin >> date;
				cout << "enter systolic value: ";
				cin >> s_value;
				cout << "enter diastolic value: ";
				cin >> d_value;
				  BP* a = new BP( date, s_value, d_value );
				this->person.addAnalysis(a);
			}
		}
		else 
			if(option == "2")
			{
				vector <MedicalAnalysis*> as = this->person.getAllAnalysis();
				for (int i = 0; i < as.size(); i++)
					cout << as[i]->toString();

			}
		else if (option == "3")
			{
				bool ill = this->person.isIll(04);
				if (ill)
					cout << "Alex is ill!\n";
				else
					cout << "Alex is not ill\n";

			}
		else if (option == "4")
			{
				string date1, date2;
				cout << "enter date 1: ";
				cin >> date1;
				cout << "enter date2: ";
				cin >> date2;
				this->person.writeToFile(date1, date2);
			}
		else if (option == "0")
				break;
		else
				cout << "INvalid input!\n";
		
	}
}