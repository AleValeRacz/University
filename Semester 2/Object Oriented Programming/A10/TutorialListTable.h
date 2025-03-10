#pragma once
#include <QAbstractTableModel>
#include "Tutorial.h"
#include <vector>
class TutorialListTable: public QAbstractTableModel
{
    Q_OBJECT

public: 
    TutorialListTable(QObject* parent = nullptr) : QAbstractTableModel(parent) {};

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setTutorials(const std::vector<Tutorial>& tutorials);

private:
    std::vector < Tutorial > tutorials;
    QStringList headers = { "Title", "Presenter", "Duration", "Linkes", "Link"};

};

