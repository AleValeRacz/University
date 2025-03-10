#include "researchGrant.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "IdeasTableModel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    IdeasTableModel* model = new IdeasTableModel{ repo };
    Researcher res = Researcher{ "adi", "senior" };
   for (Researcher res : repo.getResearchers())
    {
        researchGrant *gui = new researchGrant{model,repo, res};
        gui->show();
    }
    return a.exec();
}
