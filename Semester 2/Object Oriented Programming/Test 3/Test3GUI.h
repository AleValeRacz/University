#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Test3GUI.h"
#include "Service.h"

class Test3GUI : public QMainWindow
{
    Q_OBJECT

public:
    Test3GUI(QWidget *parent = nullptr);
    ~Test3GUI();

private:
    Ui::Test3GUIClass ui;
    Service service;
    void populateList();
    void search_documents();
    void best_match();

};
