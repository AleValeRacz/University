#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include "service.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <QMessageBox>
#include<qlabel.h>


class UserGUI : public QWidget
{
	Q_OBJECT

private:

	Service& serv;
	QListWidget* watchListWidget;
	QPushButton* switchToAdminButton;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* likeButton;
	QPushButton* nextButton;
	QPushButton* displayButton;
	QPushButton* searchButton;

	QLineEdit* searchEdit;
	vector <Tutorial> filteredTutorials;
	int searchIndex;
	void displayCurrentTutorial();
	void clearTutorialInfo();
	QLabel* tutorialInfoLabel;

	void buildGUI();
	void addButtonHandler();
	void removeButtonHandler();
	void searchButtonHandler();
	void nextButtonHandler();
	void displayButtonHandler();
	void likeButtonHandler();
public:
	UserGUI(Service& serv, QWidget* parent = nullptr);
	~UserGUI() ;
	
signals:

	void swichToAdmin();


};

