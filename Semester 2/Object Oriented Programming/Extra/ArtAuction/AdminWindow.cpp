#include "AdminWindow.h"

AdminWindow::AdminWindow(ItemManager &manager, User user, QWidget *parent): manager{manager}, user {user}, QMainWindow(parent)
{
	ui.setupUi(this);
	this->manager.addObserver(this);
	this->setWindowTitle(QString::fromStdString(user.getName()));

	this->ui.comboBox->addItem("all");
	this->ui.comboBox->addItem("furniture");
	this->ui.comboBox->addItem("electronics");
	this->update();

	QObject::connect(this->ui.comboBox, &QComboBox::currentIndexChanged, this, &AdminWindow::update);
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &AdminWindow::addItem);
	QObject::connect(this->ui.ItemsList, &QListWidget::itemSelectionChanged, this, &AdminWindow::populateOffers);
}


void AdminWindow::update()
{
	this->ui.ItemsList->clear();
	string category = this->ui.comboBox->currentText().toStdString();
	for (auto item : this->manager.getItems())
	{
		if (category == "all" || item.getCategory() == category)
			this->ui.ItemsList->addItem(QString::fromStdString(item.toString()));
	}

	this->ui.OfferList->clear();

}

void AdminWindow::populateOffers()
{
	this->ui.OfferList->clear();
	QListWidgetItem* selectedItem = this->ui.ItemsList->currentItem();
	if (selectedItem)
	{
		string name = selectedItem->text().split(",").at(0).toStdString();
		Item item = this->manager.getItemByName(name);
		{
			for (auto offer : item.getOffers())
			{
				string text = to_string(offer.id) + to_string(offer.sum) + offer.date;
				this->ui.OfferList->addItem(QString::fromStdString(text));
			}
		}
	} 
	
}

void AdminWindow::addItem()
{
	string name = ui.NameLine->text().toStdString();
	string category = ui.CategoryLine->text().toStdString();
	int price = ui.priceLine->text().toInt();
	this->manager.addItem(name, category, price);
	this->update();
}
AdminWindow::~AdminWindow()
{}
