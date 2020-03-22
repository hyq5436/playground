#include "LoadingDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingDemo w;
    w.show();
    return a.exec();
}
