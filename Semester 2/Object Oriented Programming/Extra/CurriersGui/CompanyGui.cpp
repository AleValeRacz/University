#include "CompanyGui.h"
#include "qmessagebox.h"
CompanyGui::CompanyGui(Service &serv, QWidget *parent)
	: serv{serv}, QMainWindow(parent)
{
	ui.setupUi(this);
    this->update();
    this->serv.addObserver(this);
    QObject::connect(ui.addPushButton, &QPushButton::clicked, this, &CompanyGui::addPackage);
    QObject::connect(ui.setCoordinatesButton, &QPushButton::clicked, this, &CompanyGui::updateCoord);
    QObject::connect(ui.listWidget, &QListWidget::itemSelectionChanged, this, &CompanyGui::Selected);
}

CompanyGui::~CompanyGui()
{}

void CompanyGui::update()
{
    QFont font;
    font.setBold(true);
    this->ui.listWidget->clear();
    for (auto pack : this->serv.sortPackages())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(pack.toString()));
        this->ui.listWidget->addItem(item);
        if (pack.getStatus())
            item->setBackground(Qt::green);
        else
            item->setFont(font);




    }
}


void CompanyGui::Selected()
{
    QListWidgetItem* pack = this->ui.listWidget->currentItem();
    if (pack)
    {
        this->ui.participantsList->clear();
        string recip = pack->text().split('|').at(0).toStdString();
        Package& p = this->serv.getPackageByRecipient(recip);
        this->ui.infoLineEditp->setText(QString::fromStdString( to_string(p.getLocation().first) + " "+ to_string(p.getLocation().second)));
        for (auto particip : p.getParticipants())
            this->ui.participantsList->addItem(QString::fromStdString(particip));

    }

}
void CompanyGui::updateCoord()
{

    QListWidgetItem* pack = this->ui.listWidget->currentItem();
    if (pack)
    {
        this->ui.infoLineEditp->clear();
        string recip = pack->text().split('|').at(0).toStdString();
        Package& p = this->serv.getPackageByRecipient(recip);
        //QStringList coord = this->ui.infoLineEditp->text().split(' ');
       // string x = coord[0].toStdString();
       // string y = coord[1].toStdString();
        p.setCoord(4, 5);
        this->serv.notify();
    }
}
void CompanyGui::addPackage()
{
    string receiver = this->ui.reciplineEdit->text().toStdString();
    string street = this->ui.strretlineEdit->text().toStdString();
    int nr = stoi(this->ui.NrlineEdit->text().toStdString());
    double x = stod(this->ui.XlineEdit->text().toStdString());
    double y = stod(this->ui.YlineEdit->text().toStdString());
    try 
    {
        this->serv.addPackage(receiver, street, nr, x, y, 0);
        this->serv.notify();
    }
    catch(exception &e)
    {
        QMessageBox::warning(this,"oops", e.what());
    }
   
}
