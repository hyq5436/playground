#pragma once

#include <QtWidgets/QDialog>
#include "ui_PushButtonWithMenuDemo.h"

class PushButtonWithMenuDemo : public QDialog
{
    Q_OBJECT

public:
    PushButtonWithMenuDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::PushButtonWithMenuDemoClass ui;
};
