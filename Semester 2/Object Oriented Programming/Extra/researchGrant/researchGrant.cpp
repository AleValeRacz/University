#include "researchGrant.h"

researchGrant::researchGrant(IdeasTableModel* model,Repository &repo, Researcher res, QWidget *parent)
    : model{ model }, repo { repo}, res{ res }, QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(this->res.getName()));
    ui.tableView->setModel(model);

    if (this->res.getPosition() != "senior")
    {
        this->ui.acceptButton->hide();
        this->ui.SavepushButton->hide();
    }
      
    this->ui.savebutton->hide();

    if (!this->repo.hasAccepted(this->res))
        this->ui.DeveloppushButton->hide();
    QObject::connect(ui.AddButton, &QPushButton::clicked, this, &researchGrant::AddIdea);
    QObject::connect(ui.DeveloppushButton, &QPushButton::clicked, this, &researchGrant::Develop);
    QObject::connect(ui.savebutton,&QPushButton::clicked, this, &researchGrant::SaveIdea);
    QObject::connect(ui.acceptButton, &QPushButton::clicked, this, &researchGrant::AcceptIdea);
}

researchGrant::~researchGrant()
{}

void researchGrant::AddIdea()
{
    string title = this->ui.TitlelineEdit->text().toStdString();
    string desc = this-> ui.DesclineEdit->text().toStdString();
    int duration = this->ui.DurationlineEdit->text().toInt();
    try {
        this->repo.AddIdea(title, desc, "proposed", this->res.getName(), duration);
        this->model->updateData();
    }
    catch (exception& e)
    {
        QMessageBox::warning(this, "error", e.what());
    }


}

void researchGrant::AcceptIdea()
{
    if (!this->ui.tableView->selectionModel()->selectedIndexes().isEmpty())
    {
        auto row = this->ui.tableView->selectionModel()->selectedIndexes().at(0).row();
        string title = this->model->data(model->index(row,0), Qt::DisplayRole).toString().toStdString();
        Idea &idea = this->repo.getIdeaByTitle(title);
        idea.setAccepted();
        this->model->updateData();
    }
}

void researchGrant::Develop()
{
    this->ui.savebutton->show();
    this->ui.listWidget->clear();
    for (auto &idea : this->repo.getIdeas())
    {
        if (idea.getStatus() == "accepted" && idea.getCreator() == this->res.getName())
        {
            string text = idea.getTitle() +","+ idea.getDescription() +"," + to_string(idea.getDuration());
            this->ui.listWidget->addItem(QString::fromStdString(text));
        }
    }
}

void researchGrant::SaveIdea()
{
    QListWidgetItem* selected = this->ui.listWidget->currentItem();
    string title = selected->text().split(",").at(0).toStdString();
    Idea idea = this->repo.getIdeaByTitle(title);
    string filename = title + ".txt";
    ofstream fout(filename);
    fout << idea.toString();
}
 