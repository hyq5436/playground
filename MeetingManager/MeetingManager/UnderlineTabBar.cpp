#include "UnderlineTabBar.h"

#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTextOption>

UnderlineTabBar::UnderlineTabBar(QWidget* parent) : QTabBar(parent) {}

UnderlineTabBar::~UnderlineTabBar() {}

#define USE_RED_DOT
#if defined(USE_RED_DOT)
QSize UnderlineTabBar::tabSizeHint(int index) const
{
    int textWidth = 0;
    for (int i = 0; i < count(); i++)
    {
        QString text = tabText(i);
        textWidth += this->fontMetrics().width(text);
    }
    int parentWidth = static_cast<QWidget*>(parent())->width();
    int avgWidth    = (parentWidth - textWidth) / (2 * count());
    int width       = QTabBar::tabSizeHint(index).width();
    if (textWidth < parentWidth)
    {
        width = 2 * avgWidth + this->fontMetrics().width(tabText(index));
    }
    return QSize(width, 50);
}

void UnderlineTabBar::paintEvent(QPaintEvent* event)
{
    QStylePainter   painter(this);
    QStyleOptionTab opt;

    int startPos = 0;
    for (int i = 0; i < count(); i++)
    {
        initStyleOption(&opt, i);

        QRect tabRect = opt.rect;
        if (currentIndex() == i)
        {
            painter.setPen(QColor("#333333"));
        }
        else
        {
            painter.setPen(QColor("#999999"));
        }

        QString text = tabText(i);
        painter.drawText(tabRect, tabText(i), QTextOption(Qt::AlignVCenter | Qt::AlignHCenter));

        if (currentIndex() == i)
        {
            int   lineWidth     = 20;
            int   lineHeight    = 2;
            int   paddingBottom = 5;
            int   fontHeight    = painter.fontMetrics().height();
            QRect underlineRect((opt.rect.x() + startPos + opt.rect.width() - lineWidth) / 2,
                                opt.rect.y() + (opt.rect.height() - fontHeight) / 2 + fontHeight + paddingBottom,
                                lineWidth, lineHeight);
            painter.fillRect(underlineRect, QColor("#34BB9C"));
        }

        if (currentIndex() != i)
        {
            int   textWidth  = painter.fontMetrics().width(text);
            int   textHeight = painter.fontMetrics().height();
            QRect dotRect(startPos + (opt.rect.width() - textWidth) / 2 + textWidth,
                          opt.rect.y() + (opt.rect.height() - textHeight) / 2, 4, 4);
            painter.setPen(QColor("#FF0000"));
            painter.setBrush(QBrush(QColor("#FF0000")));
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
            painter.drawEllipse(dotRect);
        }

        startPos += opt.rect.width();
    }
}

#else
QSize UnderlineTabBar::tabSizeHint(int index) const {
	QSize oldSize = QTabBar::tabSizeHint(index);
    return QSize(oldSize.width(), 50);
}

void UnderlineTabBar::paintEvent(QPaintEvent* event) {
    QStylePainter painter(this);
    QStyleOptionTab opt;

	int startPos = 0;
    for (int i = 0; i < count(); i++) {
        initStyleOption(&opt, i);

        QRect tabRect = opt.rect;
        if (currentIndex() == i) {
            painter.setPen(QColor("#333333"));
        } else {
            painter.setPen(QColor("#999999"));
        }
        painter.drawText(tabRect, tabText(i),
                         QTextOption(Qt::AlignVCenter | Qt::AlignHCenter));

        if (currentIndex() == i) {
            int lineWidth = 20;
            int lineHeight = 2;
            int paddingBottom = 5;
            int fontHeight = painter.fontMetrics().height();
            QRect underlineRect(
                (opt.rect.x() + startPos + opt.rect.width() - lineWidth) / 2,
                opt.rect.y() + (opt.rect.height() - fontHeight) / 2 +
                    fontHeight + paddingBottom,
                lineWidth, lineHeight);
            painter.fillRect(underlineRect, QColor("#34BB9C"));
        }
        startPos += opt.rect.width();
    }
}
#endif
