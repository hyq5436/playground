#include <QStyleOption>
#include <QStylePainter>
#include "LiveMoreButton.h"

#include "CommonFun.h"

LiveMoreButton::LiveMoreButton(QWidget* parent) : QPushButton(parent) {
    QStringList moreButtonStyle;
    moreButtonStyle.append(styleSheet());
    moreButtonStyle.append(
        QString("QPushButton{border-style:none;padding:5px;border-radius:3px;"
                "color:%1;background:%2;%3}")
            .arg(QString("#E1E1E1"))
            .arg(QString("#37383e"))
            .arg(QString::fromLocal8Bit(" font-family:'Microsoft YaHei';")));
    moreButtonStyle.append(QString("QPushButton:hover{color:%1;background:%2;}")
                               .arg(QString("#e1e1e1"))
                               .arg(QString("#2e2e34")));
    moreButtonStyle.append(
        QString("QPushButton:pressed{color:%1;background:%2;}")
            .arg(QString("#e1e1e1"))
            .arg(QString("#2e2e34")));

    moreButtonStyle.append(
        QString("  QPushButton::menu-indicator {"
                "      width:0px;"
                "  }"
                ""));
    setStyleSheet(moreButtonStyle.join(""));
}

LiveMoreButton::~LiveMoreButton() {}

QSize LiveMoreButton::sizeHint() const {
    return QSize(85, 32);
}

void LiveMoreButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);

    QStylePainter p(this);

    QString more("更多");
    int iTextWidth = fontMetrics().width(more) + 10;

    QRect preRect = QRect(0, 0, (width() - iTextWidth) / 2, height());
    QRect postRect = QRect(width() - (width() - iTextWidth) / 2, 0,
                           (width() - iTextWidth) / 2, height());

    p.drawText(rect(), more, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
    p.setFont(CommonFun::getIconFont());
    p.drawText(postRect, QChar(0xe638),
               QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    p.drawText(preRect, QChar(0xf705),
               QTextOption(Qt::AlignRight | Qt::AlignVCenter));
}
