#include "FloatWindowTopLayer.h"
#include "CommonFun.h"

FloatWindowTopLayer::FloatWindowTopLayer(QWidget* parent) : QFrame(parent) {
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui.lblLiveStatus->setStyleSheet(
        QString("QLabel {"
                "padding-left: 2px;"
                "padding-top: 2px;"
                "padding-right: 2px;"
                "padding-bottom: 1px;"
                "font: 12px 'Microsoft YaHei';"
                "color: #FFFFFF;"
                "background-color: #F5A623;"
                "border-top-left-radius: 2px;"
                "border-top-right-radius: 0px;"
                "border-bottom-right-radius: 6px;"
                "border-bottom-left-radius: 0px;"
                "}"));

    ui.btnClose->setStyleSheet(
        QString("QPushButton#btnClose {"
                "background-color: rgba(0,0,0,0.80);"
                "border-radius: 8px;"
                "color: white;"
                "};"));
    connect(ui.btnClose, &QPushButton::clicked, this, [this]() {
        this->close();
        emit signal_CloseWindow();
    });

    QFont iconFont = CommonFun::getIconFont();
    iconFont.setPixelSize(8);
    ui.btnClose->setFixedSize(16, 16);
    ui.btnClose->setFont(iconFont);
    ui.btnClose->setText(QChar(0xF62C));

    setHostName("胡寅秋");
    setMicStatus(false);
}

void FloatWindowTopLayer::setMicStatus(bool bMute) {
    if (bMute)
    {
        ui.hostMicStatus->setIcon(QChar(0xe64c));
    } 
    else
    {
        ui.hostMicStatus->setIcon(QChar(0xf64d));
    }
}

void FloatWindowTopLayer::setHostName(const QString& name) {
    ui.hostMicStatus->setHostName(name);
}

FloatWindowTopLayer::~FloatWindowTopLayer() {}

void FloatWindowTopLayer::resizeEvent(QResizeEvent* event) {
    resetControlPos();
    QFrame::resizeEvent(event);
}

void FloatWindowTopLayer::resetControlPos() {
    ui.lblLiveStatus->move(7, 8);
    ui.btnClose->move(width() - ui.btnClose->width() - 2, 2);
    ui.hostMicStatus->move(0, height() - ui.hostMicStatus->height());
}
