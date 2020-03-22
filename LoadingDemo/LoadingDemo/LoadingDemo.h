#pragma once

#include <QtWidgets/QWidget>
#include "ui_LoadingDemo.h"

class LoadingDemo : public QWidget
{
    Q_OBJECT

public:
    LoadingDemo(QWidget *parent = Q_NULLPTR);

public slots:
    void showLoadingDialog();

private:
    Ui::LoadingDemoClass ui;
};
