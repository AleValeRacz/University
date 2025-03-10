#include "ShoppingList.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShoppingList w;
    w.show();
    return a.exec();
}
