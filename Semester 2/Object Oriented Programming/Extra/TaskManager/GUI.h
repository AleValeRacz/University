#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TaskManager.h"
#include "Service.h"
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
    void populateList();
    void buildGUI();
    void showTasks();
private:
    Ui::TaskManagerClass ui;
    Service service;
    QListWidget* tasksList;
    QPushButton* showTasksButton;
    QLineEdit* priorityEdit;
    QListWidget* tasksSorted;
    QLabel* totalDuration;
};


