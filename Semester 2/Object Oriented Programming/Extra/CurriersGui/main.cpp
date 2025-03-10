#include "CurriersGui.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "CompanyGui.h"
#include "Map.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service serv{ repo };
    for (auto &cur : repo.GetCouriers())
    {
        CurriersGui* w = new CurriersGui(serv, cur);
        w->show();
    }
    CompanyGui* win = new CompanyGui(serv);
    win->show();
    Map* m = new Map(serv);
    m->show();
    return a.exec();
}
