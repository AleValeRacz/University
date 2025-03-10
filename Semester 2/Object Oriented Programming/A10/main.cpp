#include "Application.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Service serv;
    MainWindow mw{ serv };
    mw.show();

    return app.exec();
}
