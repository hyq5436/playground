#pragma once

#include <QFrame>
#include "ui_LiveFloatWindow.h"

class FloatWindowTopLayer;
class QCamera;
class LiveFloatWindow : public QFrame
{
    Q_OBJECT

public:
    LiveFloatWindow(QWidget *parent = Q_NULLPTR);
    ~LiveFloatWindow();

    void setPhoto(QPixmap image);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

public slots:
    void setMicStatus(bool bMute);

private:
    void resetControlPos();

private:
    Ui::LiveFloatWindow ui;
    FloatWindowTopLayer* m_pControlLayer;
    QCamera* m_pCamera;
    QPoint m_startDragPoint;
};
