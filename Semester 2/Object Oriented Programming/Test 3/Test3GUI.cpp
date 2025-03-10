#include "Test3GUI.h"

Test3GUI::Test3GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateList();
    QObject::connect(this->ui.BestMatchButton, &QPushButton::clicked, this, &Test3GUI::best_match);
    QObject::connect(this->ui.SearchLineEdit, &QLineEdit::textChanged, this, &Test3GUI::search_documents);

}

Test3GUI::~Test3GUI()
{}

void Test3GUI::populateList()
{
    this->ui.documentListWidget->clear();
    for (auto d : this->service.get_documents_sorted())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.toString()));
        this->ui.documentListWidget->addItem(item);
    }
}

void Test3GUI::search_documents()
{
    string text = this->ui.SearchLineEdit->text().toStdString();
    if (text.empty())
    {
        this->populateList();
        return;
    }
    this->ui.documentListWidget->clear();
    for (auto d : this->service.search(text))
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.toString()));
        this->ui.documentListWidget->addItem(item);
    }

}

void Test3GUI::best_match()
{
    QString text = this->ui.BestMatchEdit->text();
    string t = text.toStdString();
    string name = this->service.bestMatch(t);
    this->ui.BestMatchLabel->setText(QString::fromStdString(name));
}
