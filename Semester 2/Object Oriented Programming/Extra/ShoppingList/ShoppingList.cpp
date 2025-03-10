#include "ShoppingList.h"
#include <qobject.h>
#include <iostream>
ShoppingList::ShoppingList(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    
    this->populateList(this->service.getItemsSorted(), this->ui.ShoppinglistWidget);
    QObject::connect(this->ui.FilterButton, &QPushButton::clicked, this, &ShoppingList::FilterHandler);
    QObject::connect(this->ui.SearchButton, &QPushButton::clicked, this, &ShoppingList::SearchHandler);
    assert(this->service.getItemsSorted()[0].getCategory() == "Dairy");
}

ShoppingList::~ShoppingList()
{}

void ShoppingList::populateList(vector <Item> items, QListWidget* list)
{
    list->clear();
    for (auto i : items)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.toString()));
        list->addItem(item);
    }
}

void ShoppingList::SearchHandler()
{
    QString text = this->ui.SearchEdit->text();
    string str = text.toStdString();

    vector<Item> items = this->service.SearchNameCategory(str); 
    this->populateList(items, this->ui.ShoppinglistWidget);
}

void ShoppingList::FilterHandler()
{
    QString text = this->ui.FilterEdit->text();
    string category = text.toStdString();
    vector<Item> items = this->service.FilterByCategory(category);
    this->populateList(items, this->ui.FilteredList);
}
