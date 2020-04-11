#include "LiveFloatWindow.h"
#include "FloatWindowTopLayer.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>

#include <QDesktopWidget>
#include <QMouseEvent>

LiveFloatWindow::LiveFloatWindow(QWidget *parent)
    : QFrame(parent), m_pControlLayer(nullptr) {
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
    m_pCamera = new QCamera(this);
    m_pCamera->setCaptureMode(QCamera::CaptureVideo);
    m_pCamera->setViewfinder(ui.cameraWidget);
    ui.stackedWidget->setCurrentIndex(1);
    m_pCamera->start();
    connect(ui.stackedWidget, &QStackedWidget::currentChanged, this,
            [this](int index) {
        // 头像
        if (index == 0) {
            m_pCamera->stop();
        }
        else if (index == 1) {
            m_pCamera->start();
        }
    });
}

LiveFloatWindow::~LiveFloatWindow()
{
}

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

void LiveFloatWindow::setMicStatus(bool bMute) {}
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
            if (movePos.y() > QApplication::desktop()->availableGeometry().height() - 10) {
                movePos.setY( QApplication::desktop()->availableGeometry().height() - 10);
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
