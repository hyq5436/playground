#include "IrregularWindowDemo.h"
#include "IrregularWindow.h"

IrregularWindowDemo::IrregularWindowDemo(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton, &QPushButton::pressed, this, [this]() {
        auto* pWindow = new IrregularWindow(nullptr);
        pWindow->show();
    });
}
