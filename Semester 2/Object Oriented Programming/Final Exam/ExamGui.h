#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExamGui.h"
#include "Observer.h"
#include "Service.h"

class ExamGui : public QMainWindow,  public Observer
{
    Q_OBJECT

public:
    ExamGui(Service &serv, Courier &cur, QWidget *parent = nullptr);
    ~ExamGui();
    void deliver();
    void update() override;


private:
    Ui::ExamGuiClass ui;
    Service& serv;
    Courier& cur;

    
};
