#include "BacteriumModel.h"

BacteriumModel::BacteriumModel( Service &serv, QWidget *parent)
	: serv{ serv }, QMainWindow(parent)
{
	ui.setupUi(this);
}

BacteriumModel::~BacteriumModel()
{}

int BacteriumModel::rowCount(const QModelIndex & parent) const
{
	return this->serv.sortedBacterias().size();
}

int BacteriumModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}


QVariant BacteriumModel::data(const QModelIndex& index, int role)  const
{
	
	int row = index.row();
	int col = index.column();
	Bacterium &bac = this->serv.sortedBacterias()[row];
	if (role == Qt::DisplayRole)
	{
		if (col == 0)
			return QString::fromStdString(bac.getName());
		else if(col == 1)
			return QString::fromStdString(bac.getSpecies());
		else if(col == 2)
			return QString::fromStdString(to_string(bac.getSize()));
		else if (col == 3)
		{
			string text;
			for (string des : bac.getDesises())
				text += des+',';
			return QString::fromStdString(text);
		}
			
	}
	return QVariant();
	
}

QVariant BacteriumModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		if (section == 0)
			return "name";
		else if (section == 1)
			return "species";
		else if (section == 2)
			return "size";
		else if (section == 3)
			return "desieses";

	}
	return QVariant();
}

bool BacteriumModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

	if (role == Qt::EditRole) 
	{
		Bacterium& bac = this->serv.sortedBacterias()[index.row()];

		if (index.column() == 0)
		{
			string name = value.toString().toStdString();
			bac.setName(name);
		}
		else if (index.column() == 1)
		{
			string name = value.toString().toStdString();
			bac.setSpecies(name);
		}
		else if (index.column() == 2)
		{
			string name = value.toString().toStdString();
			bac.setSize(stoi(name));
		}
		emit this->dataChanged(index, index);
		this->UpdateData();
		return true;
	}
	return false;
}

Qt::ItemFlags BacteriumModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemFlags();
}



