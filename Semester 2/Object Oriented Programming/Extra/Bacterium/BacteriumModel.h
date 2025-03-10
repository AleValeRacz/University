#pragma once
#include <QAbstractTableModel>
#include <QMainWindow>
#include "ui_BacteriumModel.h"
#include "Service.h"

class BacteriumModel :public QMainWindow, public QAbstractTableModel
{
	Q_OBJECT

public:
	BacteriumModel(Service &serv, QWidget *parent = nullptr);
	~BacteriumModel();
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;
	void UpdateData(){ emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1)); }



private:
	Ui::BacteriumModelClass ui;
	Service& serv;

	
};
