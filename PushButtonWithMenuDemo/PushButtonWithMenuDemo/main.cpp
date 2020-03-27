#include "PushButtonWithMenuDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PushButtonWithMenuDemo w;
    w.show();
    return a.exec();
}
