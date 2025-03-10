#include "CurriersGui.h"
#include <set>
#include <qmessagebox.h>
CurriersGui::CurriersGui(Service &serv,  Courier &cur, QWidget *parent)
    : serv{ serv }, cur{ cur } , QMainWindow(parent)
{
    ui.setupUi(this);
    this->serv.addObserver(this);
    set<string> s;

    for (auto pack : this->serv.filterPackages(this->cur))
        s.insert(pack.getAdress().first);

    for (string street : s)
        this->ui.comboBox->addItem(QString::fromStdString(street));
    this->ui.comboBox->addItem("all");


    this->ui.label->setText(QString::fromStdString(to_string(this->cur.getZone().x) +" " + to_string(this->cur.getZone().y) +" "+ to_string(this->cur.getZone().rad)));
    this->update();
    this->setWindowTitle(QString::fromStdString(this->cur.getName()));
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &CurriersGui::deliver);
    //QObject::connect(ui.comboBox, &QComboBox::currentIndexChanged, this, &CurriersGui::update);
    QObject::connect(ui.sendButton, &QPushButton::clicked, this, &CurriersGui::sendMessage);
    QObject::connect(ui.checkBox, &QCheckBox::checkStateChanged, this, &CurriersGui::update);
  //  QObject::connect(ui.goingPushButton, &QPushButton::clicked, this, &CurriersGui::going);
    QObject::connect(ui.listWidget, &QListWidget::currentItemChanged, this, &CurriersGui::Selected);

}

CurriersGui::~CurriersGui()
{
}

void CurriersGui::deliver()
{

    QListWidgetItem* item = ui.listWidget->currentItem();
    if (item)
    {
        string recipient = item->text().split('|').at(0).toStdString();
        Package& pack = this->serv.getPackageByRecipient(recipient);
        pack.setDelivered();
        this->serv.notify();
    }

}

void CurriersGui::update()
{
    
    this->ui.listWidget->clear();
    string street = this->ui.comboBox->currentText().toStdString();

    for (auto pack : this->serv.filterPackages(cur))
    {
        if (pack.getStatus() == 0)
        {
            if (street == "all" || street == pack.getAdress().first)
                this->ui.listWidget->addItem(QString::fromStdString(pack.toString()));
        }
  
    }
    
    this->ui.listWidget->clear();
    vector<Package> packs;

    if (this->ui.checkBox->isChecked())
        packs = this->serv.filterPackages(this->cur);
    else
        packs = this->serv.GetPackage();

    for(auto pack: packs)
        this->ui.listWidget->addItem(QString::fromStdString(pack.toString()));

    
    /*
    this->ui.chatBox->clear();
    for (msg &mess: this->serv.getMessages())
    {
       if (mess.name != this->cur.getName())
        {
            string text = mess.name + ": " + mess.text;
            this->ui.chatBox->addItem(QString::fromStdString(text));

        }
    }
      */

}


void CurriersGui::sendMessage()
{

    string text = this->ui.msgLineEdit->text().toStdString();
    this->serv.addMessage({ this->cur.getName(), text });
    this->ui.msgLineEdit->text().clear();
    this->serv.notify();

}

void CurriersGui::Selected()
{
    QListWidgetItem* pack = this->ui.listWidget->currentItem();
    if (pack)
    {
        this->ui.chatBox->clear();
        string recip = pack->text().split('|').at(0).toStdString();
        Package &p = this->serv.getPackageByRecipient(recip);
        this->ui.chatBox->addItem(QString::fromStdString("locatia ii" + to_string(p.getLocation().first) + " latitudine " + to_string(p.getLocation().second) + " longitudine"));

    }

}

/*
void CurriersGui::going()
{
    QListWidgetItem* pack = this->ui.listWidget->currentItem();
    if (pack)
    {
        string recip = pack->text().split('|').at(0).toStdString();
        Package& p = this->serv.getPackageByRecipient(recip);
        for (auto partic : p.getParticipants())
            if (this->cur.getName() == partic)
            {
                QMessageBox::warning(this, "hopa!", "You already set you're going!");
                return;
            }
        p.addParticipant(cur.getName());
        this->serv.notify();
                


                ///////

    vector<Document> Service::search(string text)
    {
        vector<Document>  documents;
        for (auto d : this->repo.get_documents())
        {
            if (d.get_name().find(text) != string::npos)
                documents.push_back(d);
        }
        return documents;

    /// <summary>
    ///
    /// </summary>
    string text = this->ui.FilterEdit->text().toStdString();
    if (text.empty())
    {
        this->populateList();
        return;
    }
    this->ui.documentsList->clear();
    for (auto doc : this->service.search(text))
        this->ui.documentsList->addItem(QString::fromStdString(doc.toString()));
 //////
}
    
        */


