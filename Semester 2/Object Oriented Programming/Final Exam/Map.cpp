#include "Map.h"

Map::Map( Service &serv, QWidget *parent)
	: serv{ serv }, QMainWindow(parent)
{
	ui.setupUi(this);
	this->serv.addObserver(this);
}

Map::~Map()
{}

void Map::update()
{
	repaint();
}

void Map::paintEvent(QPaintEvent* event)
{
	QPainter painter{ this };

	painter.setBrush(Qt::yellow);
	for (Package& pack : this->serv.getPackages())
	{
		if (!pack.getStatus()) {
			double x = (pack.getLocation().first + width() / 2);
			double y = (-pack.getLocation().second + height() / 2);
			painter.drawEllipse(QPoint(x, y), 5, 5);
			painter.drawText(x + 5, y, QString::fromStdString(pack.getRecipient()));
		}
	}

	painter.setBrush(Qt::NoBrush);


	for (Courier& cur : this->serv.getCouriers())
	{
		int radius = static_cast<int>(cur.getZone().rad);
		double x = cur.getZone().x + width() / 2;
		double y = -cur.getZone().y + height() / 2;
		painter.drawEllipse(QPoint(x, y), radius, radius);
	}
}


