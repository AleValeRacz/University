#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CurriersGui.h"
#include "Service.h"

class CurriersGui : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    CurriersGui(Service &serv, Courier &cur, QWidget *parent = nullptr);
    ~CurriersGui();
    void deliver();
   // void polulateList();
    void update() override;
    void sendMessage();
    void Selected();
    //void going();

private:
    Ui::CurriersGuiClass ui;
    Service& serv;
    Courier& cur;

};
