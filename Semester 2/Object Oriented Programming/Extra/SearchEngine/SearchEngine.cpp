#include "SearchEngine.h"
#include <qmessagebox.h>
SearchEngine::SearchEngine(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    QObject::connect(this->ui.ShowButton,&QPushButton::clicked, this, &SearchEngine::MaxSimilarity);
    QObject::connect(this->ui.FilterEdit, &QLineEdit::textChanged, this, &SearchEngine::search);
}

SearchEngine::~SearchEngine()
{}

void SearchEngine::populateList()
{
    this->ui.documentsList->clear();
    for (auto d : this->service.getDocumentsSorted())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.toString()));
        this->ui.documentsList->addItem(item);
    }
        


}

void SearchEngine::MaxSimilarity()
{
    QString text = this->ui.SearchLineEdit->text();
    string t = text.toStdString();
    string name = this->service.bestMatch(t);
    if (name.empty())
        QMessageBox::warning(this,"opps","no matches  found;(");
    this->ui.BestMatchingLabel->setText(QString::fromStdString(name));
}

void SearchEngine::search()
{
    string text = this->ui.FilterEdit->text().toStdString();
    if (text.empty())
    {
        this->populateList();
        return;
    }
    this->ui.documentsList->clear();
    for (auto doc : this->service.search(text))
        this->ui.documentsList->addItem(QString::fromStdString(doc.toString()));


}