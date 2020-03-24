#include "UnderlineTabBar.h"

#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTextOption>

UnderlineTabBar::UnderlineTabBar(QWidget* parent) : QTabBar(parent) {}

UnderlineTabBar::~UnderlineTabBar() {}

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
