#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_researchGrant.h"
#include "Repository.h"
#include "IdeasTableModel.h"
#include "qmessagebox.h"

class researchGrant : public QMainWindow
{
    Q_OBJECT

public:
    researchGrant(IdeasTableModel* model,Repository &repo, Researcher res,QWidget *parent = nullptr);
    ~researchGrant();
    void AddIdea();
    void AcceptIdea();
    void Develop();
    void SaveIdea();
    void SaveAll();

private:
    Ui::researchGrantClass ui;
    Repository& repo;
    IdeasTableModel* model;

    Researcher res;
};
