#include "BillsBills.h"
#include <qlayout.h>
GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
{
    this->buildGUI();
    this->populateList();

    QObject::connect(this->calculateUnpainButton, &QPushButton::clicked, this, &GUI::calculateTotal);
    QObject::connect(this->checkBoxPaid, &QCheckBox::toggled, this, &GUI::filterBillsPaid);
    QObject::connect(this->checkBoxUnpaid, &QCheckBox::toggled, this, &GUI::filterBillsUnpaid);


}

GUI::~GUI()
{}

void GUI::buildGUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    this->billsListWidget = new QListWidget;
    this->companyLabel = new QLabel("company");
    this->companyEdit = new QLineEdit;
    this->calculateUnpainButton = new QPushButton("unpaid total");
    this->companyLabel = new QLabel{};
    this->checkBoxPaid = new QCheckBox;
    this->checkBoxUnpaid = new QCheckBox;
    mainLayout->addWidget(billsListWidget);
    mainLayout->addWidget(companyLabel);
    mainLayout->addWidget(companyEdit);
    mainLayout->addWidget(calculateUnpainButton);
    mainLayout->addWidget(companyLabel);
    mainLayout->addWidget(checkBoxPaid);
    mainLayout->addWidget(checkBoxUnpaid);
    this->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

}

void GUI::populateList()
{
    this->billsListWidget->clear();
    for (auto bill : this->service.get_sorted_bills())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));
        if (!bill.get_is_paid())
            item->setBackground(Qt::red);
        this->billsListWidget->addItem(item);

    }
}

void GUI::filterBillsPaid()
{

    vector <Bill> filteredBills;
    for (auto bill : this->service.get_sorted_bills())
    {
        if (bill.get_is_paid())
            filteredBills.push_back(bill);
    }
    this->billsListWidget->clear();
    for (auto bill : filteredBills)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));
        if (!bill.get_is_paid())
            item->setBackground(Qt::red);
        this->billsListWidget->addItem(item);
    }
    
}

void GUI::filterBillsUnpaid()
{
    vector <Bill> filteredBills;
    for (auto bill : this->service.get_sorted_bills())
    {
        if(!bill.get_is_paid())
            filteredBills.push_back(bill);
    }
    this->billsListWidget->clear();
    for (auto bill : filteredBills)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bill.toString()));
        if (!bill.get_is_paid())
            item->setBackground(Qt::red);
        this->billsListWidget->addItem(item);
    }

}

void GUI::calculateTotal()
{
    QString company = this->companyEdit->text();
    double total = this->service.calculate_total(company.toStdString());
    if (total != 0)
    {
        this->companyLabel->setText(QString::number(total));
    }
    else
        QMessageBox::warning(this, "Opss!", "no unpaid bills for this company found!");
}

