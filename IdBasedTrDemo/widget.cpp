#include "widget.h"
#include "./ui_widget.h"


namespace {

void initCommonString()
{
    //: 测试
    //% "测试"
    //~ 其他注释
    qtTrId("id-test");

    //: 参数测试
    //% "test %1 %2 test"
    //~ 其他注释
    qtTrId("id-param-test");
}

}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label->setText(qtTrId("id-test"));
    ui->label->setText(qtTrId("id-param-test"));
}

Widget::~Widget()
{
    delete ui;
}

