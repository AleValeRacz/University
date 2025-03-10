#include "WatchListWindow.h"


WatchListWindow::WatchListWindow( QWidget* parent) : QWidget{ parent }, tableView{ new QTableView(this) }, model(new TutorialListTable(this))
{

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    tableView->setModel(model);
    setLayout(layout);

    setWindowTitle("Watch list"); 
    resize(600, 400); 
}

void WatchListWindow::setTutorials(vector<Tutorial>& tut)
{
    this->model->setTutorials(tut);
}
