 #pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include "service.h"
#include <qpushbutton.h>

class AdminGUI : public QWidget
{
    Q_OBJECT
private:
    Service &serv;
    QListWidget* tutorialListWidget;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* switchToUserButton;
    QLineEdit* titleEdit;
    QLineEdit* presenterEdit;
    QLineEdit* durationEdit;
    QLineEdit* likesEdit;
    QLineEdit* linkEdit;

signals:
    void switchToUser();

public:
    AdminGUI(Service &serv);
    ~AdminGUI();
   
private:
    void buildGUI();
    void populateList();
    void addButtonHandler();
    void RemoveButtonHandler();
    void UpdateButtonHandler();
   
};
