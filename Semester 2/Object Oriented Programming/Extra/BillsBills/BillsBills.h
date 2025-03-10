#pragma once
#include "Service.h"
#include <QtWidgets/QMainWindow>
#include "ui_BillsBills.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <qcheckbox.h>
#include <QMessageBox>

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
    void populateList();
    void buildGUI();
    void calculateTotal();
    void filterBillsPaid();
    void filterBillsUnpaid();


private:
    Service service;
    QListWidget* billsListWidget;
    QPushButton* calculateUnpainButton;
    QCheckBox * checkBoxUnpaid;
    QCheckBox* checkBoxPaid;
    QLineEdit* companyEdit;
    QLabel* companyLabel;
    Ui::BillsBillsClass ui;
};
