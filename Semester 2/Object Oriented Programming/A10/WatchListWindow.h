#pragma once

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "TutorialListTable.h"
#include "Service.h"
class WatchListWindow : public QWidget
{
	Q_OBJECT
public:
	WatchListWindow(QWidget* parent = nullptr);
	~WatchListWindow() {};

	void setTutorials(vector<Tutorial>& tutorials);
private:
	QTableView* tableView;
	TutorialListTable* model;
	QVBoxLayout* layout;

};

