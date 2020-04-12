#include "LiveFloatWindow.h"
#include "FloatWindowTopLayer.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>

#include <QDesktopWidget>
#include <QMouseEvent>

LiveFloatWindow::LiveFloatWindow(QWidget* parent)
    : QFrame(parent),
      m_pControlLayer(nullptr),
      m_pCamera(nullptr),
      m_strCameraName(QString("")),
      m_bEnableCamera(false) {
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    m_pControlLayer = new FloatWindowTopLayer(this);
    m_pControlLayer->setGeometry(geometry());
    m_pControlLayer->show();
    m_pControlLayer->move(pos());

    connect(m_pControlLayer, &FloatWindowTopLayer::signal_CloseWindow,
            [this]() {
                this->close();
                this->deleteLater();
            });

    ui.cameraWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    ui.stackedWidget->setCurrentIndex(0);
}

LiveFloatWindow::~LiveFloatWindow() {}

void LiveFloatWindow::setPhoto(QPixmap image) {
    ui.lblPhoto->setPixmap(image);
}

void LiveFloatWindow::resizeEvent(QResizeEvent* event) {
    resetControlPos();
    QFrame::resizeEvent(event);
}

void LiveFloatWindow::resetControlPos() {
    m_pControlLayer->setGeometry(geometry());
    m_pControlLayer->move(pos());
}

void LiveFloatWindow::setHostName(const QString& name) {
    m_pControlLayer->setHostName(name);
}

void LiveFloatWindow::setMicStatus(bool bMute) {
    m_pControlLayer->setMicStatus(bMute);
}

void LiveFloatWindow::setCameraName(const QString& name) {
    if (name == m_strCameraName || name.isEmpty()) {
        return;
    }
    m_strCameraName = name;

    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo& cameraInfo : cameras) {
        if (cameraInfo.description() == m_strCameraName) {
            if (m_pCamera != nullptr)
            {
                m_pCamera->stop();
                m_pCamera->deleteLater();
            }
            m_pCamera = new QCamera(cameraInfo, this);
            m_pCamera->setCaptureMode(QCamera::CaptureVideo);
            m_pCamera->setViewfinder(ui.cameraWidget);
        }
    }

    if (m_bEnableCamera) {
        enableCamera(true);
    }
}

void LiveFloatWindow::enableCamera(bool bEnable) {
    if (bEnable == m_bEnableCamera) {
        return;
    }
    m_bEnableCamera = bEnable;
    if (m_bEnableCamera)
    {
        m_pCamera->start();
        ui.stackedWidget->setCurrentIndex(1);
    } else {
        m_pCamera->stop();
        ui.stackedWidget->setCurrentIndex(0);
    }
}

void LiveFloatWindow::mousePressEvent(QMouseEvent* mouseEvent) {
    QFrame::mousePressEvent(mouseEvent);

    if (mouseEvent->button() == Qt::LeftButton) {
        m_startDragPoint = mouseEvent->globalPos() - frameGeometry().topLeft();
    }
}

void LiveFloatWindow::mouseMoveEvent(QMouseEvent* mouseEvent) {
    QFrame::mouseMoveEvent(mouseEvent);

    bool bLeftButtonClicked = false;
    if (mouseEvent->buttons() & Qt::LeftButton) {
        bLeftButtonClicked = true;
    } else {
        bLeftButtonClicked = false;
    }

    if (!m_startDragPoint.isNull() && bLeftButtonClicked) {
        QPoint movePos = mouseEvent->globalPos() - m_startDragPoint;
        if (!movePos.isNull()) {
            if (movePos.y() >
                QApplication::desktop()->availableGeometry().height() - 10) {
                movePos.setY(
                    QApplication::desktop()->availableGeometry().height() - 10);
            }
            move(movePos);
            resetControlPos();
        }
    }
}

void LiveFloatWindow::mouseReleaseEvent(QMouseEvent* mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        m_startDragPoint = QPoint();
    }
    QFrame::mouseReleaseEvent(mouseEvent);
}
