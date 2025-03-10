#include "Map.h"
#include <QPainter>

Map::Map(Service &serv,QWidget *parent)
	: serv{ serv }, QWidget(parent)
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

void Map::paintEvent(QPaintEvent * event)
{

	QPainter painter{ this };

	painter.drawLine(QPoint(width() / 2, 0), QPoint(width() / 2, height()));
	painter.drawLine(QPoint(0, height() / 2), QPoint(width(), height() / 2));
	painter.setBrush(Qt::yellow);
	for (Package &pack : this->serv.GetPackage())
	{
		if (!pack.getStatus()) {
			double x = (pack.getLocation().first + width() / 2);
			double y = (-pack.getLocation().second + height() / 2);
			painter.drawEllipse(QPoint(x, y), 5, 5);
			painter.drawText(x + 5, y, QString::fromStdString(pack.getRecipient()));
		}
	}

	painter.setBrush(Qt::NoBrush);
	
	
	for (Courier& cur : this->serv.GetCouriers())
	{
		int radius = static_cast<int>(cur.getZone().rad);
		double x = cur.getZone().x + width() / 2;
		double y = cur.getZone().y + height() / 2;
		painter.drawEllipse(QPoint(x, y),radius,radius);
	}
	


}
