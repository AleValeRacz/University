#include "CompanyGui.h"

CompanyGui::CompanyGui( Service &serv,QWidget *parent)
	: serv{ serv },QMainWindow(parent)
{
	ui.setupUi(this);
	this->serv.addObserver(this);


	this->setWindowTitle("Courier Company");

	this->update();
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &CompanyGui::addPackage);

}

CompanyGui::~CompanyGui()
{}

void CompanyGui::update()
{

	this->ui.listWidget->clear();
	for (auto pack : this->serv.getPackages())
	{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(pack.toString()));
		this->ui.listWidget->addItem(item);
		if (pack.getStatus())
			item->setBackground(Qt::green);


	}
}

void CompanyGui::addPackage()
{

	string recipient = this->ui.nameLineEdit->text().toStdString();
	string street = this->ui.streetLineEdit->text().toStdString();
	string nr = this->ui.NrlineEdit->text().toStdString();
	string x = this->ui.XLineEdit->text().toStdString();
	string y = this->ui.YlineEdit->text().toStdString();
	
	this->serv.addPackage(recipient, street, stoi(nr), stod(x), stod(y), 0);
	this->serv.notify();
}


