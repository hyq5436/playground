#pragma execution_character_set("utf-8")

#include "OptionPushButton.h"
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>

#include "CommonFun.h"

namespace {
    const double ARROR_X_RELATIVE_POS = 0.875;
    const double ARROR_RECT_WIDTH = 0.125;
}

OptionPushButton::OptionPushButton(QWidget *parent)
    : QPushButton(parent), m_pMenu(nullptr)
{
    setMouseTracking(true);
}

OptionPushButton::~OptionPushButton()
{
}

bool OptionPushButton::event(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(e));
        break;
    case QEvent::MouseButtonPress:
        return handleMousePressEvent(static_cast<QMouseEvent*>(e));
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

bool OptionPushButton::handleMouseMoveEvent(QMouseEvent* e)
{
    QRect arrowRect = getArrowRect();
    if (arrowRect.contains(e->pos()))
    {
        QCursor cursor(Qt::PointingHandCursor);
        this->setCursor(cursor);
    }
    else
    {
        QCursor cursor(Qt::ArrowCursor);
        this->setCursor(cursor);
    }
    return true;
}

bool OptionPushButton::handleMousePressEvent(QMouseEvent* e)
{
    QAction* action = nullptr;
    QRect arrowRect = getArrowRect();
    if (shouldShowMenu() && arrowRect.contains(e->pos())) {
        action = showMenu();
        if (action == nullptr) {
            return true;
        }
    }

    if (isOptionEnabled())
    {
        action = getCheckedAction();
    }
    emit signal_ActionButtonPressed(action);
    return true;
}

QRect OptionPushButton::getArrowRect()
{
    return QRect(width() * ARROR_X_RELATIVE_POS, 0, width() * ARROR_RECT_WIDTH, height());
}

void OptionPushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    if (shouldShowMenu())
    {
        QPainter p(this);
        p.setFont(CommonFun::getIconFont());
        p.drawText(getArrowRect(), QChar(0xe718),
            QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
    }
}

void OptionPushButton::addMenu(QMenu* menu)
{
    if (menu == nullptr)
    {
        return;
    }
    m_pMenu = menu;
}

QAction* OptionPushButton::showMenu()
{
    if (m_pMenu == nullptr)
    {
        return nullptr;
    }
    return m_pMenu->exec(mapToGlobal(QPoint(0, height())));
}

bool OptionPushButton::shouldShowMenu()
{
    if (m_pMenu == nullptr || m_pMenu->actions().size() < 2)
    {
        return false;
    } 
    else
    {
        return true;
    }
}

bool OptionPushButton::isOptionEnabled()
{
    if (m_pMenu == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QAction* OptionPushButton::getCheckedAction()
{
    for(QAction *action : m_pMenu->actions())
    {
        if (action->isChecked()) {
            return action;
        }
    }
    return nullptr;
}
