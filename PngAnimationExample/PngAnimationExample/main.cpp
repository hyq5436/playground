#include "PngAnimationExample.h"
#include <QtWidgets/QApplication>
#include "AnimatedLabel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnimatedLabel bt("process-working.png", 8);
    bt.setFixedSize(500, 500);
    bt.show();


    return a.exec();
}
