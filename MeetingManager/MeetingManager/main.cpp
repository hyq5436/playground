#include "MeetingManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MeetingManager w;
    w.show();
    return a.exec();
}
