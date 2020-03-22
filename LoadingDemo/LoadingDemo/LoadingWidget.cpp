#include "LoadingWidget.h"
#include <QGraphicsDropShadowEffect>
LoadingWidget::LoadingWidget(QWidget *parent)
    : QFrame(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    //ÊµÀýÒõÓ°shadow
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(4);
    shadow->setOffset(0, 2);
    shadow->setColor(QColor("#999999"));
    setGraphicsEffect(shadow);

    setStyleSheet("QFrame{ background-color: white; border-radius: 8px; }");
}

LoadingWidget::~LoadingWidget()
{
}
