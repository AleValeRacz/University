#pragma once
#include "Observer.h"
#include "ItemManager.h"
#include <QMainWindow>
#include "ui_AdminWindow.h"

class AdminWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	AdminWindow(ItemManager &manager, User user, QWidget *parent = nullptr);
	void update() override;
	//void populateItems();
	void populateOffers();
	void addItem();
	~AdminWindow();

private:
	ItemManager &manager;
	User user;
	Ui::AdminWindowClass ui;

};
