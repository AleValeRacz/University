#include "ExamGui.h"
#include "set"
ExamGui::ExamGui( Service &serv,Courier  &cur,QWidget *parent)
    : serv{ serv }, cur{ cur },QMainWindow(parent)
{
    ui.setupUi(this);
    this->serv.addObserver(this);
    this->setWindowTitle(QString::fromStdString(this->cur.getName()));
    this->ui.Zonelabel->setText(QString::fromStdString(to_string(this->cur.getZone().x) + " " + to_string(cur.getZone().y) + " " + to_string(cur.getZone().rad)));


    


    this->ui.comboBox->addItem("all");
    set<string> streets;
    for (auto st : this->cur.getStreets())
        streets.insert(st);
    for (auto str : streets)
        this->ui.comboBox->addItem(QString::fromStdString(str));

    QObject::connect(ui.comboBox, &QComboBox::currentIndexChanged, this, &ExamGui::update);
    QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &ExamGui::deliver);

    this->update();
}

ExamGui::~ExamGui()
{}

void ExamGui::deliver()
{

        QListWidgetItem* item = ui.listWidget->currentItem();
        if (item)
        {
            string recipient = item->text().split('|').at(0).toStdString();
            Package& pack = this->serv.getPackagaByRecipient(recipient);
            pack.setDelivered();
            this->serv.notify();
        }

    
}

void ExamGui::update()
{

    this->ui.listWidget->clear();
    string street = this->ui.comboBox->currentText().toStdString();

    for (auto pack : this->serv.filteredPackages(this->cur))
    {
        if (pack.getStatus() == 0)
        {
            if (street == "all" || street == pack.getAdress().first)
                this->ui.listWidget->addItem(QString::fromStdString(pack.toString()));
        }

    }

}




