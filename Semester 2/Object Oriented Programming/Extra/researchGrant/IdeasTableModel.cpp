#include "IdeasTableModel.h"

int IdeasTableModel::rowCount(const QModelIndex& parent) const
{
  
    return this->repo.getIdeas().size();
}

int IdeasTableModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant IdeasTableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    Idea idea = this->repo.getIdeas()[row];
    if (role == Qt::DisplayRole)
        switch (column)
        {
        case 0:
            return QString::fromStdString(idea.getTitle());
        case 1:
            return QString::fromStdString(idea.getDescription());
        case 2:
            return QString::fromStdString(idea.getStatus());
        case 3:
            return QString::fromStdString(idea.getCreator());
        case 4:
            return QString::fromStdString(to_string(idea.getDuration()));
        default:
            break;
        }
    return QVariant();

}

QVariant IdeasTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return "Title";
        case 1:
            return "Description";
        case 2:
            return "Status";
        case 3:
            return  "Creator";
        case 4:
            return "Duration";
        default:
            break;
        }
    }
    return QVariant();
}

void IdeasTableModel::updateData()
{
    beginResetModel();
    endResetModel();
    emit this->dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

bool IdeasTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole)
    {
        Idea &idea = this->repo.getIdeas()[index.row()];
        if (index.column() == 1)
        {
            string desc = value.toString().toStdString();
            idea.setDescription(desc);
        }
        emit this->dataChanged(index, index);
        return true;
    }
    
    return false;
}

Qt::ItemFlags IdeasTableModel::flags(const QModelIndex& index) const
{
    int col = index.column();
    if (col != 1 &&  col!=0)
        return Qt::ItemFlags();
    return Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled ;
}




