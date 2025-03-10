#include "UserGUI.h"
 



UserGUI::UserGUI(Service& serv, QWidget* parent)
	: QWidget(parent), serv(serv), searchIndex(0)
{
	this->buildGUI();
	//QObject::connect(this->switchToAdminButton, &QPushButton::clicked, this, &UserGUI::swichToAdmin);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addButtonHandler);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &UserGUI::removeButtonHandler);
	QObject::connect(this->searchButton, &QPushButton::clicked, this, &UserGUI::searchButtonHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::nextButtonHandler);
	QObject::connect(this->displayButton, &QPushButton::clicked, this, &UserGUI::displayButtonHandler);
	QObject::connect(this->likeButton, &QPushButton::clicked, this, &UserGUI::likeButtonHandler);
}
UserGUI::~UserGUI()
{

}

void UserGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	this->watchListWidget = new QListWidget{};
	mainLayout->addWidget(watchListWidget);

	QGridLayout* rightLayout = new QGridLayout{};

	QLabel* searchPresenterLabel = new QLabel{ "enter presenter: " };
	this->searchEdit = new QLineEdit{};

	rightLayout->addWidget(searchPresenterLabel, 0, 0);
	rightLayout->addWidget(this->searchEdit, 0, 1);
	this->tutorialInfoLabel = new QLabel{};
	rightLayout->addWidget(this->tutorialInfoLabel, 1, 0, 1, 2);

	//this->switchToAdminButton = new QPushButton{ "Switch to admin" };
	this->addButton = new QPushButton{ "Add to watchlist" };
	this->removeButton = new QPushButton{ "Remove from watchlist" };
	this->searchButton = new QPushButton{ "Search" };
	this->nextButton = new QPushButton{ "Next" };
	this->likeButton = new QPushButton{ "Like" };
	this->displayButton = new QPushButton{ "Display watchlist" };
	
	//rightLayout->addWidget(this->switchToAdminButton, 2, 0);
	rightLayout->addWidget(this->searchButton, 2, 1);
	rightLayout->addWidget(this->addButton, 2, 2);
	rightLayout->addWidget(this->removeButton, 2, 3);
	rightLayout->addWidget(this->nextButton, 2, 4);
	rightLayout->addWidget(this->likeButton, 2, 5);
	rightLayout->addWidget(this->displayButton, 2, 0);

	mainLayout->addLayout(rightLayout);

}

void UserGUI::displayCurrentTutorial() 
{
	if (this->searchIndex < this->filteredTutorials.size())
	{
		Tutorial t = this->filteredTutorials[searchIndex];
		QString info = QString::fromStdString(t.to_string());
		this->tutorialInfoLabel->setText(info);
		this->serv.play_tutorial(t);
	}
	
}

void UserGUI::clearTutorialInfo() 
{
	this->tutorialInfoLabel->clear();
}

void UserGUI::addButtonHandler()
{

	if (this->filteredTutorials.empty()) 
	{
		QMessageBox::warning(this, "Warning", "No tutorials available to add!");
		return;
	}

	if (this->searchIndex >= 0 && this->searchIndex < this->filteredTutorials.size())
	{
			 Tutorial t = filteredTutorials[searchIndex];
			 try
			 {
				 this->serv.add_to_watchlist(t);



				 QString itemText = QString::fromStdString(t.get_title()) + " | " +
					 QString::fromStdString(t.get_presenter()) + " | " +
					 QString::number(t.get_minutes()) + " " +
					 QString::number(t.get_seconds()) + " | " +
					 QString::number(t.get_likes()) + " | " +
					 QString::fromStdString(t.get_link());

				 this->watchListWidget->addItem(itemText);
			 }
			 catch (Exception& e)
			 {
				 QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
			 }
		
	}
	else {
		QMessageBox::warning(this, "Warning", "Current index is out of bounds!");
	}
}




void UserGUI::removeButtonHandler()
{
	QListWidgetItem* selectedItem = this->watchListWidget->currentItem();

	if (selectedItem)
	{
		try {


			QString title = selectedItem->text().split(" | ").at(0);
			this->watchListWidget->takeItem(this->watchListWidget->row(selectedItem));

			this->serv.remove_from_watchlist(title.toStdString());
		}
		catch (Exception& e)
		{
			QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
		}
	}
}

void UserGUI::searchButtonHandler()
{
	QString presenter = this->searchEdit->text();
	if (presenter.isEmpty())
	{
		this->filteredTutorials = this->serv.get_tutorials();
		this->searchIndex;
		
	}
	else
	{
		this->filteredTutorials = this->serv.filter_by_presenter(presenter.toStdString());
		this->searchIndex = 0;
	}

	if (this->filteredTutorials.empty()) 
	{
		QMessageBox::information(this, "Info", "No tutorials found for the given presenter.");
		this->clearTutorialInfo();
		return;
	}

	this->displayCurrentTutorial();
}


void UserGUI::nextButtonHandler()
{
	if (!this->filteredTutorials.empty())
	{
		this->searchIndex = (this->searchIndex + 1) % this->filteredTutorials.size();
		this->displayCurrentTutorial();
	}
}
void UserGUI::displayButtonHandler()
{
	try {
		this->serv.dislay_watchlist();
	}
	catch (Exception& e)
	{
		QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
	}
}
void UserGUI::likeButtonHandler()
{
	QListWidgetItem* selectedItem = this->watchListWidget->currentItem();

	if (selectedItem) {
		QString title = selectedItem->text().split(" | ").at(0);
		this->watchListWidget->takeItem(this->watchListWidget->row(selectedItem));
		this->serv.like_tutorial(title.toStdString());


	}

}

