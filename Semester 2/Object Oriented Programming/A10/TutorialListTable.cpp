#include "TutorialListTable.h"
#include <QAbstractTableModel>



int TutorialListTable::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return this->tutorials.size();
}

int TutorialListTable::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return this->headers.size();
}

QVariant TutorialListTable::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Tutorial& tutorial = this->tutorials[index.row()];
    QString duration = QString::number(tutorial.get_minutes()) + " " + QString::number(tutorial.get_seconds());
    switch (index.column()) {
    case 0: return QString::fromStdString(tutorial.get_title());
    case 1: return QString::fromStdString(tutorial.get_presenter());
    case 2: return duration;
    case 3: return QString::number(tutorial.get_likes());
    case 4: return QString::fromStdString(tutorial.get_link());
    default: return QVariant();
    }
}

QVariant TutorialListTable::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return headers[section];
    }
    else {
        return QString::number(section + 1);
    }
}

void TutorialListTable::setTutorials(const std::vector<Tutorial>& tut) {
    beginResetModel();
    this->tutorials = tut;
    endResetModel();
}