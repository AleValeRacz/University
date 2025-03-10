#pragma once
#include <qabstractitemmodel.h>
#include <Repository.h>
class IdeasTableModel :
    public QAbstractTableModel
{
private:
    Repository& repo;
public:
    IdeasTableModel(Repository &repo): repo{repo}{}
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void updateData();
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

};

