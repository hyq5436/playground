#include "CameraDemo.h"
#include <QDebug>
#include <QPushButton>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>

bool checkCameraAvailability()
{
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras)
        qDebug() << cameraInfo.deviceName();

    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

CameraDemo::CameraDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras)
        qDebug() << cameraInfo.deviceName();

    m_pCamera = new QCamera(this);
    connect(ui.btnStop, &QPushButton::pressed, this, [this]() {
        m_pCamera->stop();
    });
    connect(ui.btnShowCamera, &QPushButton::pressed, this, [this]() {
        if (!checkCameraAvailability())
        {
            qDebug() << "Camera Not Avaliable";
        }
        m_pCamera->setCaptureMode(QCamera::CaptureVideo);
        m_pCamera->setViewfinder(ui.widget);
        qDebug() << "errorCode: " << m_pCamera->error();
        qDebug() << "error: " << m_pCamera->errorString();
        qDebug() << "status: " << m_pCamera->status();
        m_pCamera->start();
    });
}
