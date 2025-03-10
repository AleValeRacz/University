#include "ColectionerWindow.h"

ColectionerWindow::ColectionerWindow(ItemManager& manager, User user, QWidget* parent) : manager{ manager }, user{ user }, QWidget(parent)
{
	ui.setupUi(this);
	this->manager.addObserver(this);
	this->setWindowTitle(QString::fromStdString(user.getName()));
	this->update();
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &ColectionerWindow::Bid);
	QObject::connect(this->ui.ItemsList, &QListWidget::itemSelectionChanged, this, &ColectionerWindow::populateOffers);
}

ColectionerWindow::~ColectionerWindow()
{}


void ColectionerWindow::update()
{ 
	this->ui.ItemsList->clear();
	for (auto item : this->manager.getItems())
		this->ui.ItemsList->addItem(QString::fromStdString(item.toString()));
	this->ui.OffersList->clear();

}

void ColectionerWindow::populateOffers()
{
	this->ui.OffersList->clear();
	QListWidgetItem* selectedItem = this->ui.ItemsList->currentItem();
	if (selectedItem)
	{
		string name = selectedItem->text().split(",").at(0).toStdString();
		Item item = this->manager.getItemByName(name);
		for (auto offer : item.getOffers())
		{
			string text = to_string(offer.id) + to_string(offer.sum) + offer.date;
			this->ui.OffersList->addItem(QString::fromStdString(text));
		}
	}

}

void ColectionerWindow::Bid()
{
	QListWidgetItem* selectedItem = this->ui.ItemsList->currentItem();
	if (selectedItem)
	{
		int offeredSum = ui.lineEdit->text().toInt();
		string name = selectedItem->text().split(",").at(0).toStdString();
		Item item = this->manager.getItemByName(name);
		this->manager.updatePriceOffers(item.getName(), offeredSum, this->user.getId(), offeredSum, "12-12-2024");
		this->update();
	}
	
}