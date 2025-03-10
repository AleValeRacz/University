#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ArtAction.h"

class ArtAction : public QMainWindow
{
    Q_OBJECT

public:
    ArtAction(QWidget *parent = nullptr);
    ~ArtAction();

private:
    Ui::ArtActionClass ui;
};
