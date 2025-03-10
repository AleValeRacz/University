 #pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include "service.h"
#include <qpushbutton.h>
#include <qshortcut.h>

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
    QPushButton* undoButton;
    QPushButton* redoButton;
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;

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
    void handleUndo();
    void handleRedo();
   
};
