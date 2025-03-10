#include "Test3GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test3GUI w;
    w.show();
    return a.exec();
}
