#include "AdminGUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <QMessageBox>

AdminGUI::AdminGUI(Service& serv):serv{serv}
{
	this->buildGUI();
	this->populateList();
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::RemoveButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::UpdateButtonHandler);
	connect(undoButton, &QPushButton::clicked, this, &AdminGUI::handleUndo);
	connect(redoButton, &QPushButton::clicked, this, &AdminGUI::handleRedo);
	connect(undoShortcut, &QShortcut::activated, this, &AdminGUI::handleUndo);
	connect(redoShortcut, &QShortcut::activated, this, &AdminGUI::handleRedo);
	//QObject::connect(switchToUserButton, &QPushButton::clicked, this,  & AdminGUI::switchToUser);
}

AdminGUI::~AdminGUI()
{
}

void AdminGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	this->tutorialListWidget = new QListWidget{};
	mainLayout->addWidget(tutorialListWidget);

	QGridLayout* rightLayout = new QGridLayout{};

	QLabel* titleLabel = new QLabel{ "Title" };
	this->titleEdit = new QLineEdit{};
	QLabel* presenterLabel = new QLabel{ "Presenter" };
	this->presenterEdit = new QLineEdit{};
	QLabel* durationLabel = new QLabel{ "Duration" };
	this->durationEdit = new QLineEdit{};
	QLabel* likesLabel = new QLabel{ "Likes" };
	this->likesEdit = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Link" };
	this->linkEdit = new QLineEdit{};

	this->undoButton = new QPushButton("Undo");
	this->redoButton = new QPushButton("Redo");

	rightLayout->addWidget(titleLabel, 0, 0);
	rightLayout->addWidget(this->titleEdit, 0, 1);
	rightLayout->addWidget(presenterLabel, 1, 0);
	rightLayout->addWidget(this->presenterEdit, 1, 1);
	rightLayout->addWidget(durationLabel, 2, 0);
	rightLayout->addWidget(this->durationEdit, 2, 1);
	rightLayout->addWidget(likesLabel, 3, 0);
	rightLayout->addWidget(this->likesEdit, 3, 1);
	rightLayout->addWidget(linkLabel, 4, 0);
	rightLayout->addWidget(this->linkEdit, 4, 1);


	this->addButton = new QPushButton{ "Add" };
	this->removeButton = new QPushButton{ "Remove" };
	this->updateButton = new QPushButton{ "Update" };
	//this->switchToUserButton = new QPushButton{ "Switch to user" };

	rightLayout->addWidget(this->addButton, 5, 0);
	rightLayout->addWidget(this->removeButton, 5, 1);
	rightLayout->addWidget(this->updateButton, 5, 2);
	rightLayout->addWidget(this->undoButton, 5, 3);
	rightLayout->addWidget(this->redoButton, 5, 4);
	//rightLayout->addWidget(this->switchToUserButton, 5, 3);;

	this->undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	this->redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);

	mainLayout->addLayout(rightLayout);
}

void AdminGUI::populateList()
{
	this->tutorialListWidget->clear();
	for (auto t : this->serv.get_tutorials())
	{
		QString itemText = QString::fromStdString(t.get_title()) + " | " +
			QString::fromStdString(t.get_presenter()) + " | " +
			QString::number(t.get_minutes()) + " " +
			QString::number(t.get_seconds()) + " | " +
			QString::number(t.get_likes()) + " | " +
			QString::fromStdString(t.get_link());

		this->tutorialListWidget->addItem(itemText);
	}
}

void AdminGUI::addButtonHandler()
{ 
	try
	{
		QString title = this->titleEdit->text();
		QString presenter = this->presenterEdit->text();
		QString duration = this->durationEdit->text();
		QString likes = this->likesEdit->text();
		QString link = this->linkEdit->text();
		QStringList durationParts = duration.split(" ");
		int minutes = durationParts[0].toInt();
		int seconds = durationParts[1].toInt();
		Tutorial t = Tutorial(title.toStdString(), presenter.toStdString(), { minutes,seconds }, likes.toInt(), link.toStdString());
		this->serv.add_tutorial(t);
		this->populateList();
	}
	catch (Exception& e)
	{
		QMessageBox::warning(this, "Error",QString::fromStdString(e.getMessage()));
	}
}

void AdminGUI::RemoveButtonHandler()
{

		QListWidgetItem* selectedItem = tutorialListWidget->currentItem();

		if (selectedItem) {
			QString title = selectedItem->text().split(" | ").at(0);
			tutorialListWidget->takeItem(tutorialListWidget->row(selectedItem));
			try
			{
				serv.remove_tutorial(title.toStdString());
			}
			catch (Exception& e)
			{
				QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
			}
		}
}

void AdminGUI::UpdateButtonHandler()
{
	QString presenter = this->presenterEdit->text();
	QString duration = this->durationEdit->text();
	QString likes = this->likesEdit->text();
	QString link = this->linkEdit->text();
	QStringList durationParts = duration.split(" ");
	int minutes = durationParts[0].toInt();
	int seconds = durationParts[1].toInt();
	
	QListWidgetItem* selectedItem = tutorialListWidget->currentItem();
	if (selectedItem)
	{
		
		try
		{
			QString title = selectedItem->text().split(" | ").at(0);
			serv.update_tutorial(title.toStdString(), presenter.toStdString(), minutes, seconds, likes.toInt(), link.toStdString());
			this->populateList();
		}
		catch (Exception& e)
		{
			QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
		}

		
	}
}

void AdminGUI::handleUndo()
{
	try
	{
		this->serv.undo();
		this->populateList();
	}
	catch (Exception& e)
	{
		QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
	}

}

void AdminGUI::handleRedo()
{
	try
	{
		this->serv.redo();
		this->populateList();
	}
	catch (Exception& e)
	{
		QMessageBox::warning(this, "Error", QString::fromStdString(e.getMessage()));
	}

}

