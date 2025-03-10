#include "Ui.h"


void Ui::print_menu()
{
	cout << "1.Remove client.\n 2.Show clients and dwellings\n 3.Add dwelling\n, 4.Save clients to file\n";

}

void Ui::start()
{
	while (true)
	{
		this->print_menu();
		int option = 0;
		cout << "option: ";
		cin >> option;
		if (option == 1)
		{
			cout << "name: ";
			string name;
			cin >> name;
			this->ag.removeClient(name);

		}
		else if (option == 2)
		{
			vector<Client*> cls = this->ag.get_clients();
			vector<Dwelling*> dw = this->ag.get_dwellings();
			for (int i = 0; i < cls.size(); i++)
			{
				cout << cls[i]->toString();
				for (int j = 0; j < dw.size(); j++)
					if (cls[i]->isInterested(dw[j]))
						cout << "client interested in dwelling with price " << dw[j]->get_price() << endl;
			}



		}
		else if (option == 3)
		{
			double price;
			bool isProfi;
			cout << "price: ";
			cin >> price;
			cout << "is profitable (0,1)?: ";
			cin >> isProfi;
			vector<Client*> cls = this->ag.addDwelling(price, isProfi);
			for (int i = 0; i < cls.size(); i++)
				cout << cls[i]->toString();
		}
		else if (option == 4)
			this->ag.writeToFile("agestates.txt");
	}
}
