#include "IrregularWindowDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IrregularWindowDemo w;
    w.show();
    return a.exec();
}
