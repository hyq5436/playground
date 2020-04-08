#include "LiveButton.h"

#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>

#include "CommonFun.h"

LiveButton::LiveButton(QWidget *parent)
    : QPushButton(parent)
{
}

LiveButton::~LiveButton()
{
}

bool LiveButton::event(QEvent* e) {
    switch (e->type()) {
        case QEvent::MouseMove:
            handleMouseMoveEvent(static_cast<QMouseEvent*>(e));
            break;
        case QEvent::MouseButtonPress:
            //return handleMousePressEvent(static_cast<QMouseEvent*>(e));
            break;
        default:
            break;
    }
    return QPushButton::event(e);
}

bool LiveButton::handleMouseMoveEvent(QMouseEvent* e) {
    QCursor cursor(Qt::PointingHandCursor);
    this->setCursor(cursor);
    return true;
}

void LiveButton::paintEvent(QPaintEvent* event) {
    //QPushButton::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 220 * 260
    // 152 * 152
    int radius = 152;
    QRect outRect = QRect((width() - 152) / 2, 10, 152, 152);
    QRect inRect = QRect((width() - 138) / 2, 17, 138, 138);

    p.setPen(QPen(QColor("#37383e")));
    p.setBrush(QBrush(QColor("#37383e")));
    p.drawEllipse(inRect);

    QPainterPath path;
    path.addEllipse(outRect);
    path.addEllipse(inRect);
    p.setPen(QPen(QColor("#226058")));
    p.setBrush(QBrush(QColor("#226058")));
    p.drawPath(path);

    QFont font = CommonFun::getIconFont();
    font.setPixelSize(78);
    p.setFont(font);
    p.setPen(QPen(QColor("#00bf99")));
    p.drawText(inRect, QChar(0xf64d),
               QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}
