#pragma once

#include <QMainWindow>
#include "ui_CompanyGui.h"
#include "service.h"
#include "Observer.h"
class CompanyGui : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	CompanyGui(Service &serv, QWidget *parent = nullptr);
	~CompanyGui();
	void update() override;
	void addPackage();


private:
	Ui::CompanyGuiClass ui;
	Service& serv;
	

};
