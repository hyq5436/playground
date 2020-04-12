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

public slots:
    void setMicStatus(bool bMute);
    void setHostName(const QString& name);

signals:
    void signal_CloseWindow();

private:
    Ui::FloatWindowTopLayer ui;
};
