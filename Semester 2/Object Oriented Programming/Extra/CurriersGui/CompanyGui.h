#pragma once
#include "Service.h"
#include <QMainWindow>
#include "ui_CompanyGui.h"

class CompanyGui : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	CompanyGui(Service& serv, QWidget *parent = nullptr);
	~CompanyGui();
	void update() override;
	void addPackage();
	void Selected();
	void updateCoord();

private:
	Ui::CompanyGuiClass ui;
	Service& serv;
};
