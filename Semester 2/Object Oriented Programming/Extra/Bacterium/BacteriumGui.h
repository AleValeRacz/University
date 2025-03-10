#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BacteriumGui.h"
#include "Service.h"
#include "BacteriumModel.h"
#include <QSortFilterProxyModel>
class BacteriumGui : public QMainWindow
{
    Q_OBJECT

public:
    BacteriumGui(Service &serv, BacteriumModel* model,  Biologist &bio, QWidget *parent = nullptr);
    ~BacteriumGui();
    void addBacterium();
    void addDesiese();
    void showDesieses();
    void populateFiltered();


private:
    Ui::BacteriumGuiClass ui;
    Service& serv;
    Biologist& bio;
    QSortFilterProxyModel *filteredModel;
    BacteriumModel* model;


};
