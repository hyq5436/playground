#pragma once

#include <QtWidgets/QWidget>
#include "ui_CameraDemo.h"

class QCamera;
class CameraDemo : public QWidget
{
    Q_OBJECT

public:
    CameraDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::CameraDemoClass ui;
    QCamera* m_pCamera;
};
