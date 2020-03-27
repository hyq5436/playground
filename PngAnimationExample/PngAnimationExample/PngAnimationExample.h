#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PngAnimationExample.h"

class PngAnimationExample : public QMainWindow
{
    Q_OBJECT

public:
    PngAnimationExample(QWidget *parent = Q_NULLPTR);

private:
    Ui::PngAnimationExampleClass ui;
};
