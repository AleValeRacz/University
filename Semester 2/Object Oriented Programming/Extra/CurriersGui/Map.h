#pragma once

#include <QWidget>
#include "ui_Map.h"
#include "Service.h"

class Map : public QWidget, public Observer
{
	Q_OBJECT

public:
	Map(Service &serv,QWidget *parent = nullptr);
	~Map();
protected:
	void update() override;
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::MapClass ui;
	Service& serv;
	
};
