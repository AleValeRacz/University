#include "Ui.h"
#include "Service.h"
void Ui::print_menu()
{
	cout << "1>add car\n2.Show all cars\n3.Save to file\n";

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
			string bodyStyle, EngineType;
			int autonomy;
			cout << "enter bodyStyle: ";
			cin >> bodyStyle;
			cout << "enter engine Type: ";
			cin >> EngineType;
			//if (EngineType == "Electric")
				cout << "enter autonomy: ";
				cin >> autonomy;

				double price =this-> service.addCar(bodyStyle, EngineType, autonomy);
				cout << "price is " << price<<endl;
		}
		else if (choice == 2)
		{
			vector <Car*> cars= this->service.getCars();

			for (int i = 0; i < cars.size(); i++)
				cout << cars[i]->get_bodystyle() << " " << cars[i]->get_engine()->toString()<<" "<<cars[i]->computePrice()<<endl;
		}
		else if (choice == 3)
		{
			double price1;
			cout << "enter price :";
			cin >> price1;
			this->service.writeToFile("file.txt", price1);
		}
		else if (choice == 0)
		{

		}
		else
			cout << "Invalid input!\n";

	}
}
