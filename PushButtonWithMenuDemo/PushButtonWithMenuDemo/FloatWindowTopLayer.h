#pragma once

#include <QFrame>
#include "ui_FloatWindowTopLayer.h"

class FloatWindowTopLayer : public QFrame
{
    Q_OBJECT

public:
    FloatWindowTopLayer(QWidget *parent = Q_NULLPTR);
    ~FloatWindowTopLayer();

    void resetControlPos();

protected:
    void resizeEvent(QResizeEvent* event);

signals:
    void signal_CloseWindow();

private:
    Ui::FloatWindowTopLayer ui;
};
