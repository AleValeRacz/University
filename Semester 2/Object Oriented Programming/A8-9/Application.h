#pragma once


#include <QWidget>
#include <QPushButton>
#include "Service.h"
#include "AdminGUI.h"
#include "UserGUI.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(Service &service);
    ~MainWindow();

private:
    void openAdminMode();
    void openUserModeCSV();
    void openUserModeHTML();
    Service& service;
    QPushButton* adminModeButton;
    QPushButton* userModeCSVButton;
    QPushButton* userModeHTMLButton;
    QLabel* title;
};


