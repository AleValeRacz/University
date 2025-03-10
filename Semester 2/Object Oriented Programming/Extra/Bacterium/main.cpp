#include "BacteriumGui.h"
#include <QtWidgets/QApplication>
#include <assert.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service service{ repo };
    auto* model = new BacteriumModel{ service };
    for (auto &bio : service.getBiologists())
    {
        BacteriumGui* w = new BacteriumGui{ service,model,bio };
        w->show();
    }

    return a.exec();
}
