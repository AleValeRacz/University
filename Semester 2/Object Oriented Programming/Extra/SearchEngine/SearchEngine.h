#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SearchEngine.h"
#include "Service.h"

class SearchEngine : public QMainWindow
{
    Q_OBJECT

public:
    SearchEngine(QWidget *parent = nullptr);
    ~SearchEngine();

private:
    Ui::SearchEngineClass ui;
    void populateList();
    Service service;
    void MaxSimilarity();
    void search();
};
