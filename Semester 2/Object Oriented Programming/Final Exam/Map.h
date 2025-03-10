#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Service.h"
#include "qpainter.h"

class Map : public QMainWindow,  public Observer
{
	Q_OBJECT

public:
	Map(Service& serv, QWidget *parent = nullptr);
	~Map();
	void update() override;
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::MapClass ui;
	Service& serv;

};
