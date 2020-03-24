#pragma execution_character_set("utf-8")
#include "MeetingListViewDelegate.h"
#include <QApplication>
#include <QCursor>
#include <QDateTime>
#include <QDebug>
#include <QIcon>
#include <QItemDelegate>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QPainter>
#include <QPainter>
#include <QRect>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTooltip>

namespace {
    const QString FONT_FAMILY = "Microsoft Yahei";
    const int TITLE_FONT_SIZE = 14;
    const int CREATOR_FONT_SIZE = 13;
    const int BUTTON_FONT_SIZE = 12;
};

MeetingListViewDelegate::MeetingListViewDelegate(QWidget* parent)
    : QStyledItemDelegate(parent), m_parent(parent)
{
}

MeetingListViewDelegate::~MeetingListViewDelegate() { }

void MeetingListViewDelegate::paint(QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if (option.state & QStyle::State_Selected) {
        QBrush brush(QColor("#c7e2fb"));
        QRect fill_rect(option.rect.x(),
            option.rect.y(),
            option.rect.width(),
            option.rect.height());
        painter->fillRect(fill_rect, brush);
    } else if (option.state & QStyle::State_MouseOver) {
        QBrush brush(QColor("#e2effc"));
        QRect fill_rect(option.rect.x(),
            option.rect.y(),
            option.rect.width(),
            option.rect.height());
        painter->fillRect(fill_rect, brush);
    }

    QString iType = index.data(MLRT_MEETING_TYPE).toInt();

    //头像显示区域
    painter->setRenderHint(QPainter::Antialiasing);
    QRect iconRect = QRect(option.rect.x() + MLVDParam::iPaddingLeft,
                           option.rect.y() + MLVDParam::iIconPaddingTop,
                           MLVDParam::iIconWidth,
                           MLVDParam::iIconHeight);
    painter->setPen(QColor("#4290F4"));
    painter->setBrush(QColor("#4290F4"));
    painter->drawEllipse(iconRect);

    // 绘制按钮
    QRect detailOrJoinRect = getDatailOrJoinRect(option);
    QRect launchRect = getLaunchRect(option);
    drawButton(painter, detailOrJoinRect, QString("查看"));
    drawButton(painter, launchRect, QString("再次发起"));

    // 主题字体
    QFont font;
    font.setFamily(FONT_FAMILY);
    font.setPixelSize(TITLE_FONT_SIZE);
    painter->setFont(font);
    painter->setPen(QColor("#444444"));

    // 主题
    QString title = index.data(MLRT_TOPIC).toString();
    QRect titleRect = QRect(option.rect.x() + MLVDParam::iPaddingLeft + MLVDParam::iIconWidth + MLVDParam::iPaddingBetweenIconAndTopic,
        option.rect.y() + MLVDParam::iTopicPaddingTop,
        m_parent->width(),
        MLVDParam::iTopicHeight);
    painter->drawText(titleRect, title, QTextOption(Qt::AlignVCenter));

    // 作者字体
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(CREATOR_FONT_SIZE);
    painter->setFont(font);
    painter->setPen(QColor("#999999"));

    // 作者 HH:MM (直播号xxxx)
    QString creator = index.data(MLRT_CREATOR).toString();
    QRect creatorRect = QRect(option.rect.x() + MLVDParam::iPaddingLeft + MLVDParam::iIconWidth + MLVDParam::iPaddingBetweenIconAndTopic,
        option.rect.y() + MLVDParam::iTopicPaddingTop + MLVDParam::iTopicHeight + MLVDParam::iPaddingBetweenTopicAndCreator,
        m_parent->width(),
        MLVDParam::iCreatorAndTimeHeight);
    painter->drawText(creatorRect, creator, QTextOption(Qt::AlignVCenter));

}

QSize MeetingListViewDelegate::sizeHint(const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    return QSize(m_parent->width(), MLVDParam::iRowHeight);
}

bool MeetingListViewDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int iFinished = index.data(MLRT_MEETING_STATUS).toInt();
    QRect detailOrJoinRect = getDatailOrJoinRect(option);
    QRect launchRect = getLaunchRect(option);
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = (QMouseEvent*)event;
        if (detailOrJoinRect.contains(e->pos()))
        {
            //emit signal_BookmarkOperate(index, 0);
        }
        else if (launchRect.contains(e->pos()))
        {
            //emit signal_BookmarkOperate(index, 1);
        }
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* e = (QMouseEvent*)event;
        if (detailOrJoinRect.contains(e->pos()))
        {
            QCursor cursor(Qt::PointingHandCursor);
            QApplication::setOverrideCursor(cursor);
            QToolTip::showText(e->globalPos(), "查看");
        }
        else if (launchRect.contains(e->pos()))
        {
            QCursor cursor(Qt::PointingHandCursor);
            QApplication::setOverrideCursor(cursor);
            QToolTip::showText(e->globalPos(), "再次发起");
        }
        else
        {
            QCursor cursor(Qt::ArrowCursor);
            QApplication::setOverrideCursor(cursor);
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void MeetingListViewDelegate::drawButton(QPainter* painter, const QRect& rect, const QString& text) const
{
    QFont font;
    font.setFamily(FONT_FAMILY);
    font.setPixelSize(BUTTON_FONT_SIZE);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor("#bbbbbb"));

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setFont(font);
    painter->setPen(pen);
    painter->setBrush(QBrush());
    painter->drawRoundedRect(rect, 2, 2);
    pen.setColor(QColor("#666666"));
    painter->setPen(pen);
    painter->drawText(rect, Qt::AlignCenter, text);
}

QRect MeetingListViewDelegate::getDatailOrJoinRect(const QStyleOptionViewItem& option) const
{
    QFont font;
    font.setFamily(FONT_FAMILY);
    font.setPixelSize(BUTTON_FONT_SIZE);

    QFontMetrics fm(font);
    int iButtonWidth = qMax(fm.boundingRect(QString("查看")).width(), MLVDParam::iMinimumButtonWidth);

    return QRect(option.rect.x() + option.rect.width() - MLVDParam::iPaddingRight - iButtonWidth,
        option.rect.y() + MLVDParam::iButtonPaddingTop, iButtonWidth, MLVDParam::iButtonHeight);
}

QRect MeetingListViewDelegate::getLaunchRect(const QStyleOptionViewItem& option) const
{
    QRect detailRect = getDatailOrJoinRect(option);
    QFont font;
    font.setFamily(FONT_FAMILY);
    font.setPixelSize(BUTTON_FONT_SIZE);

    QFontMetrics fm(font);
    int iButtonWidth = qMax(fm.boundingRect(QString("再次发起")).width(), MLVDParam::iMinimumButtonWidth);

    return QRect(detailRect.x() - MLVDParam::iPaddingButton - iButtonWidth,
        detailRect.y(),
        iButtonWidth,
        MLVDParam::iButtonHeight);
}

QString MeetingListViewDelegate::getSecondLine(const QModelIndex& index) const
{
    int type = index.data(MLRT_MEETING_TYPE).toInt();
    QString creator = index.data(MLRT_CREATOR).toString();
    QString number = index.data(MLRT_MEETING_NUMBER).toString();
    QString createTime = QDateTime::fromMSecsSinceEpoch(index.data(MLRT_TIME).toLongLong()).time().toString("HH:mm");
    if (type == 0)
    {
        return QString("%1 %2 (%3%4)").arg(creator).arg(createTime).arg("直播号").arg(number);
    }
    else {
        return QString("%1 %2").arg(creator).arg(createTime);
    }
}
