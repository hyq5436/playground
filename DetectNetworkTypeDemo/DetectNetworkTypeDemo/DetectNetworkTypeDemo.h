#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DetectNetworkTypeDemo.h"

class DetectNetworkTypeDemo : public QMainWindow
{
    Q_OBJECT

public:
    DetectNetworkTypeDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DetectNetworkTypeDemoClass ui;
};
