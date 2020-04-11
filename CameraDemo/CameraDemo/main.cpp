#include "CameraDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraDemo w;
    w.show();
    return a.exec();
}
