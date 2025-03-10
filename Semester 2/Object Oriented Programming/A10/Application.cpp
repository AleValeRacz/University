#include "Application.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(Service& service): service(service)
{
    QVBoxLayout* mainLayout = new QVBoxLayout{ this };

    adminModeButton = new QPushButton{ "Admin Mode" };
    userModeCSVButton = new QPushButton{ "User Mode (CSV)" };
    userModeHTMLButton = new QPushButton{ "User Mode (HTML)" };
    QLabel* titleLabel = new QLabel{ "C++ tutorials" };
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(adminModeButton);
    mainLayout->addWidget(userModeCSVButton);
    mainLayout->addWidget(userModeHTMLButton);

    connect(adminModeButton, &QPushButton::clicked, this, &MainWindow::openAdminMode);
    connect(userModeCSVButton, &QPushButton::clicked, this, &MainWindow::openUserModeCSV);
    connect(userModeHTMLButton, &QPushButton::clicked, this, &MainWindow::openUserModeHTML);
}

MainWindow::~MainWindow() {}

void MainWindow::openAdminMode()
{
    AdminGUI* adminGUI = new AdminGUI(service);
    adminGUI->show();
}

void MainWindow::openUserModeCSV()
{
   this->service.set_type_watchlist(new CSVWatchList{ "CSVWatchList.csv" });
    UserGUI* userGUI = new UserGUI(service);
    userGUI->show();
}

void MainWindow::openUserModeHTML()
{
   this->service.set_type_watchlist(new HTMLWatchList{ "HTMLWatchList.html" });
    UserGUI* userGUI = new UserGUI(service);
    userGUI->show();
}