#include "widget.h"
#include "ui_widget.h"

#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
#ifdef GLOBAL_MACRO_DEMO
    ui->label->setText(QStringLiteral("Global Macro Demo"));
#endif
}

Widget::~Widget()
{
    delete ui;
}
