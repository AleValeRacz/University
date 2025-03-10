#include "ArtAction.h"
#include <QtWidgets/QApplication>
#include "ItemManager.h"
#include "AdminWindow.h"
#include "ColectionerWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    ItemManager manager{ repo };
    for (auto user : repo.getUsers())
    {
        if (user.getType() == "admin")
        {
            auto* window = new AdminWindow(manager, user);
            window->show();
        }
        else
        {
            auto* window = new ColectionerWindow(manager, user);
            window->show();
        }
    }

    return a.exec();
}
