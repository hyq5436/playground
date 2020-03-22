#pragma once

#include <QFrame>
#include "ui_LoadingWidget.h"

class LoadingWidget : public QFrame
{
    Q_OBJECT

public:
    LoadingWidget(QWidget *parent = Q_NULLPTR);
    ~LoadingWidget();

private:
    Ui::LoadingWidget ui;
};
