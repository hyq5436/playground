#pragma once

#include <QFrame>
#include "ui_LiveFloatWindow.h"

class FloatWindowTopLayer;
class QCamera;
class LiveFloatWindow : public QFrame {
    Q_OBJECT

public:
    LiveFloatWindow(QWidget* parent = Q_NULLPTR);
    ~LiveFloatWindow();

    void setPhoto(QPixmap image);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

public slots:
    void setHostName(const QString& name);
    void setMicStatus(bool bMute);
    void setCameraName(const QString& name);
    void enableCamera(bool bEnable);

private:
    void resetControlPos();

private:
    Ui::LiveFloatWindow ui;
    QPoint m_startDragPoint;
    FloatWindowTopLayer* m_pControlLayer;

    QCamera* m_pCamera;
    QString m_strCameraName;
    bool m_bEnableCamera;
};
