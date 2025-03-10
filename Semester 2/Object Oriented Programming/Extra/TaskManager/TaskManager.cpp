#include "GUi.h"

GUI::GUI(QWidget* parent)
    : QMainWindow(parent)
{
    this->buildGUI();
    this->populateList();
}

GUI::~GUI()
{}

void GUI::populateList()
{
    this->tasksList->clear();
    QFont bold;
    bold.setBold(true);
    for (auto t : this->service.get_tasks_sorted())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(t.toString()));
        if (t.get_priority() == 1)
            item->setFont(bold);
        this->tasksList->addItem(item);
    }
}

void GUI::buildGUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    this->tasksList = new QListWidget;
    this->showTasksButton = new QPushButton("Show tasks and duration");
    this->priorityEdit = new QLineEdit;
    this->totalDuration = new QLabel{};
    this->tasksSorted = new QListWidget;

    mainLayout->addWidget(tasksList);
    mainLayout->addWidget(showTasksButton);
    mainLayout->addWidget(priorityEdit);
    mainLayout->addWidget(tasksSorted);
    mainLayout->addWidget(totalDuration);
    QObject::connect(this->showTasksButton, &QPushButton::clicked, this, &GUI::showTasks);
    this->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
}

void GUI::showTasks()
{
    QString priority = this->priorityEdit->text();
    this->tasksSorted->clear();
    int total = 0;
    for (auto t : this->service.get_tasks_sorted())
    {
        if (t.get_priority() == priority.toInt())
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(t.toString()));
            total += t.get_duration();
            this->tasksSorted->addItem(item);
        }
    }
    if (total != 0)
        this->totalDuration->setText(QString::number(total));
    else
        QMessageBox::warning(this, "Opss", "no tasks found!");

}
