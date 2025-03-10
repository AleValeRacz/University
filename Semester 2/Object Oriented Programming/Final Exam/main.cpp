#include "ExamGui.h"
#include <QtWidgets/QApplication>

#include "CompanyGui.h"
#include "Map.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service serv{ repo };

    for (auto& cour : serv.getCouriers())
    {
        ExamGui* gui =  new ExamGui{ serv, cour };
        gui->show();

    }
    CompanyGui* comp = new CompanyGui{ serv };
    comp->show();
    Map* map = new Map{ serv };
    map->show();

    
    return a.exec();
}
