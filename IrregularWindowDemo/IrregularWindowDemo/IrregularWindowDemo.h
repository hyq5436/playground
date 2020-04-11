#pragma once

#include <QtWidgets/QDialog>
#include "ui_IrregularWindowDemo.h"

class IrregularWindowDemo : public QDialog
{
    Q_OBJECT

public:
    IrregularWindowDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::IrregularWindowDemoClass ui;
};
