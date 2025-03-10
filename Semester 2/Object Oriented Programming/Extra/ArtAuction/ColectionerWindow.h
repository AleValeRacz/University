#pragma once
#include <QWidget>
#include "ui_ColectionerWindow.h"
#include "Observer.h"
#include "ItemManager.h"

class ColectionerWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ColectionerWindow(ItemManager& manager, User user, QWidget *parent = nullptr);
	~ColectionerWindow();
	void update() override;
	void populateOffers();
	void Bid();
private:
	Ui::ColectionerWindowClass ui;
	ItemManager& manager;
	User user;
};
