#include "BacteriumGui.h"
#include <set>
BacteriumGui::BacteriumGui(Service&serv,BacteriumModel* model, Biologist& bio,QWidget *parent)
    : serv{ serv }, model{ model }, bio {
    bio
}, QMainWindow(parent)
{

   
    this->filteredModel = new QSortFilterProxyModel();
    this->filteredModel->setSourceModel(this->model);
    ui.setupUi(this);
    this->ui.tableView->setModel(this->filteredModel);
    this->setWindowTitle(QString::fromStdString(this->bio.getName()));


    set<string> species;
    for (auto spec : this->bio.getSpecies())
        species.insert(spec);
    for (auto spec : species)
        this->ui.comboBox->addItem(QString::fromStdString(spec));
    this->ui.comboBox->addItem("all");
    QObject::connect(ui.addPushButton, &QPushButton::clicked, this, &BacteriumGui::addBacterium);

    this->populateFiltered();

    QObject::connect(ui.comboBox, &QComboBox::currentIndexChanged, this, &BacteriumGui::populateFiltered);
    QObject::connect(this->ui.tableView->selectionModel(),& QItemSelectionModel::selectionChanged, this, & BacteriumGui::showDesieses);
    QObject::connect(ui.desiesePushButton, &QPushButton::clicked, this, &BacteriumGui::addDesiese);


}

BacteriumGui::~BacteriumGui()
{}

void BacteriumGui::addBacterium()
{
    string name = this->ui.nameLineEdit->text().toStdString();
    string species = this->ui.sleciesLineEdit->text().toStdString();
    int nr = stoi(this->ui.sizeLineEdit->text().toStdString());
    string desieses = this->ui.desiesesLineEdit->text().toStdString();
    string des;
    vector<string> bacterias;
    istringstream is(desieses);
    while (getline(is, des,','))
    {
        istringstream iss(des);
        string d;
        getline(iss, d, ',');
        bacterias.push_back(d);
    }
    this->serv.addBacterium(name, species, nr, bacterias);
    this->model->UpdateData();
 

    
}

void BacteriumGui::addDesiese()
{
    string text = this->ui.newDesiseslineEdit->text().toStdString();
    auto row = this->ui.tableView->selectionModel()->selectedIndexes().at(0).row();
    string name = this->ui.tableView->model()->data(ui.tableView->model()->index(row, 0), Qt::DisplayRole).toString().toStdString();
    Bacterium& bac = this->serv.getBacteriumByName(name);
    bac.addDesiese(text);
    this->model->UpdateData();

}

void BacteriumGui::showDesieses()
{

    auto row  = this->ui.tableView->selectionModel()->selectedIndexes().at(0).row();
    string name = this->ui.tableView->model()->data(ui.tableView->model()->index(row, 0), Qt::DisplayRole).toString().toStdString();
    Bacterium& bac = this->serv.getBacteriumByName(name);
    this->ui.listWidget->clear();
    for (auto des : bac.getDesises())
        this->ui.listWidget->addItem(QString::fromStdString(des));

}

void BacteriumGui::populateFiltered()
{
    if (ui.comboBox->currentText() != "all")
    {
        this->filteredModel->setFilterRegularExpression(QRegularExpression(ui.comboBox->currentText()));
        this->filteredModel->setFilterKeyColumn(1);

    }
    else
        this->filteredModel->setFilterRegularExpression("");


   

}
