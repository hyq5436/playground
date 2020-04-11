#include "AutoHideMenuBarDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoHideMenuBarDemo w;
    w.show();
    return a.exec();
}
