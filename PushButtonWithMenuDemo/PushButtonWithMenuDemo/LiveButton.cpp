#include "LiveButton.h"

#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>

#include "CommonFun.h"

namespace {
const int LIVE_BUTTON_HEIGHT = 72;
const int ICON_RECT_LENGTH = 36;
const int ICON_RECT_TOP = 8;
const int ICON_HIGHLIGHT_EDGE_WIDTH = 2;
const int ICON_NORMAL_EDGE_WIDTH = 1;
const int TEXT_MARGIN_TOP = 5;

const QColor HIGHLIGHT_COLOR = QColor("#34BB9A");
const QColor BACKGROUND_COLOR = QColor("#37383E");
const QColor NORMAL_ICON_COLOR = QColor(255, 255, 255);
const QColor NORMAL_TEXT_COLOR = QColor(255, 255, 255, 153);
const QColor NORMAL_EDGE_COLOR = QColor(255, 255, 255, 61);
const QColor HIGHLIGHT_EDGE_COLOR = QColor(52, 187, 154, 61);

}  // namespace

LiveButton::LiveButton(QWidget* parent) : QPushButton(parent) {
    setMouseTracking(true);
}

LiveButton::~LiveButton() {}

QSize LiveButton::sizeHint() const {
    int width = this->fontMetrics().width(text());

    width = qMax<int>(width, QPushButton::sizeHint().width());
    width = qMax<int>(width, ICON_RECT_LENGTH);

    return QSize(72, LIVE_BUTTON_HEIGHT);
}

bool LiveButton::event(QEvent* e) {
    switch (e->type()) {
        case QEvent::MouseMove:
            handleMouseMoveEvent(static_cast<QMouseEvent*>(e));
            break;
        case QEvent::MouseButtonPress:
            if (handleMousePressEvent(static_cast<QMouseEvent*>(e))) {
                return true;
            }
            break;
        case QEvent::MouseButtonDblClick:
            return true;
            break;
    }
    return QPushButton::event(e);
}

bool LiveButton::handleMouseMoveEvent(QMouseEvent* e) {
    QRect outRect = QRect((width() - ICON_RECT_LENGTH) / 2, ICON_RECT_TOP,
                          ICON_RECT_LENGTH, ICON_RECT_LENGTH);
    if (outRect.contains(e->pos())) {
        QCursor cursor(Qt::PointingHandCursor);
        this->setCursor(cursor);
    } else {
        QCursor cursor(Qt::ArrowCursor);
        this->setCursor(cursor);
    }

    return true;
}

bool LiveButton::handleMousePressEvent(QMouseEvent* e) {
    QRect outRect = QRect((width() - ICON_RECT_LENGTH) / 2, ICON_RECT_TOP,
                          ICON_RECT_LENGTH, ICON_RECT_LENGTH);
    if (!outRect.contains(e->pos())) {
        e->ignore();
        return true;
    }

    return false;
}

void LiveButton::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect outRect = QRect((width() - ICON_RECT_LENGTH) / 2, ICON_RECT_TOP,
                          ICON_RECT_LENGTH, ICON_RECT_LENGTH);
    QRect inRect;
    QRect textRect;
    int iEdgeWidth = ICON_NORMAL_EDGE_WIDTH;
    QChar  icon       = m_normalIcon;
    QString text       = this->text();
    QColor edgeColor = NORMAL_EDGE_COLOR;
    QColor textColor = NORMAL_TEXT_COLOR;
    QColor iconColor = NORMAL_ICON_COLOR;
    if (isCheckable() && isChecked())
    {
        iEdgeWidth = ICON_HIGHLIGHT_EDGE_WIDTH;
        edgeColor = HIGHLIGHT_EDGE_COLOR;
        textColor = HIGHLIGHT_COLOR;
        iconColor = HIGHLIGHT_COLOR;
        if (!m_checkedIcon.isNull())
        {
            icon = m_checkedIcon;
        }
        if (!m_checkedText.isEmpty())
        {
            text = m_checkedText;
        }
    }
    inRect = QRect(outRect.x() + iEdgeWidth, outRect.y() + iEdgeWidth,
                   ICON_RECT_LENGTH - 2 * iEdgeWidth,
                   ICON_RECT_LENGTH - 2 * iEdgeWidth);

    int iTextOffset = ICON_RECT_TOP + outRect.height() + TEXT_MARGIN_TOP;
    textRect =
        QRect(0, iTextOffset, width(), height() - iTextOffset);

    // 绘制icon背景
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(BACKGROUND_COLOR));
    p.drawEllipse(inRect);

    // 绘制icon同心圆
    QPainterPath path;
    path.addEllipse(outRect);
    path.addEllipse(inRect);
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(edgeColor));
    p.drawPath(path);

    // 绘制icon
    QFont oldFont = p.font();
    QFont font = CommonFun::getIconFont();
    font.setPixelSize(18);
    p.setFont(font);
    p.setPen(QPen(iconColor));
    p.drawText(inRect, icon,
               QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));

    // 绘制文本
    p.setFont(oldFont);
    p.drawText(textRect, text, QTextOption(Qt::AlignHCenter | Qt::AlignTop));
}

void LiveButton::setData(QChar icon, const QString& text)
{
    setText(text);
    m_normalIcon = icon;
}

void LiveButton::setIcon(QChar normalIcon)
{
    m_normalIcon = normalIcon;
}

void LiveButton::setCheckedIcon(QChar checkedIcon)
{
    m_checkedIcon = checkedIcon;
}

void LiveButton::setCheckedText(const QString& text)
{
    m_checkedText = text;
}

