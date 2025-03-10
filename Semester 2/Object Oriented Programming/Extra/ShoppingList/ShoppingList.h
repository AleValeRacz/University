#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ShoppingList.h"
#include "Service.h"

class ShoppingList : public QMainWindow
{
    Q_OBJECT

public:
    ShoppingList(QWidget *parent = nullptr);
    ~ShoppingList();

private:
    Service service;
    Ui::ShoppingListClass ui;
    void SearchHandler();
    void FilterHandler();
    void populateList(vector <Item> items, QListWidget* list);
    
};
