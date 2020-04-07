#include "HeadAndStatusWidget.h"
#include "CommonFun.h"

#include <QStylePainter>


HeadAndStatusWidget::HeadAndStatusWidget(QWidget *parent)
    : QWidget(parent)
{
}

HeadAndStatusWidget::~HeadAndStatusWidget()
{
}

void HeadAndStatusWidget::paintEvent(QPaintEvent* event) {
    QStylePainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), CommonFun::getRoundedImage("Resources/head.png", 200));

    QRect statusBackgroundRect(width() * 2 / 3 - 10, width() * 2 / 3 - 10 , width() / 3 + 10,
                     width() / 3 + 10);
    painter.setPen(QPen(QColor("#37383e")));
    painter.setBrush(QColor("#37383e"));
    //painter.drawEllipse(statusBackgroundRect);

    QRect statusRect(width() * 2 / 3, width() * 2 / 3, width() / 3, width() / 3);
    painter.setPen(QPen(QColor("#979797")));
    painter.setBrush(QColor("#979797"));
    painter.drawEllipse(statusRect);

    QFont iconFont = CommonFun::getIconFont();
    iconFont.setPixelSize(48);
    painter.setFont(iconFont);
    painter.setPen(QPen(QColor("#FFFFFF")));
    painter.drawText(statusRect, QChar(0xe707),
                     QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}
