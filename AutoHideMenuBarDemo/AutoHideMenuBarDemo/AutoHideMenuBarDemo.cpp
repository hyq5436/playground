#include "AutoHideMenuBarDemo.h"
#include "ShareDesktopToolbar.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>

AutoHideMenuBarDemo::AutoHideMenuBarDemo(QWidget *parent)
    : QDialog(parent), m_pToolbar(nullptr), m_pShowToolbarTimer(nullptr)
{
    ui.setupUi(this);

    setMouseTracking(true);
    m_pToolbar = new ShareDesktopToolbar(this);
    m_pShowToolbarTimer = new QTimer(this);
    connect(m_pShowToolbarTimer, &QTimer::timeout, this, [this]() {
        m_pToolbar->hideToolbar();
        //m_pToolbar->hide();
    });
}

bool AutoHideMenuBarDemo::eventFilter(QObject *watched, QEvent *event)
{
    return QDialog::eventFilter(watched, event);
}

void AutoHideMenuBarDemo::mouseMoveEvent(QMouseEvent *event)
{
    static auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    static bool bNeedShow = isMouseInRect(event);
    bool bShowStatusChanged = (bNeedShow != isMouseInRect(event));
    // if (!bNeedShow && bShowStatusChanged)
    qDebug() << "bNeedShow: " << bNeedShow << "; Change? " << bShowStatusChanged;
    if (bShowStatusChanged)
    {
        bNeedShow = isMouseInRect(event);
        if (bNeedShow)
        {
            start = std::chrono::steady_clock::now();
            end = std::chrono::steady_clock::now();
        }
    }
    else
    {
        end = std::chrono::steady_clock::now();
    }

    long long   count = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    qDebug() << "bNeedShow: " << bNeedShow << "; Change? " << bShowStatusChanged << "; count: " << count;
    if (bNeedShow && count >= 100)
    {
        startTimer(false);
        ShowToolbar(true);
    }
    else
    {
        startTimer(true);
    }
}

void AutoHideMenuBarDemo::startTimer(bool bStart)
{
    if (bStart)
    {
        m_pShowToolbarTimer->start(1000);
    }
    else
    {
        m_pShowToolbarTimer->stop();
    }
}

bool AutoHideMenuBarDemo::isMouseInRect(QMouseEvent* event)
{
    QRect parentRect = geometry();
    QPoint point = QPoint(parentRect.x(), parentRect.y() + parentRect.height() - m_pToolbar->height());
    QRect toolBarRect = QRect(point, QSize(parentRect.width(), 100));
    return toolBarRect.contains(mapToGlobal(event->pos()));
}

void AutoHideMenuBarDemo::ShowToolbar(bool bShow)
{
    if (m_pToolbar == nullptr)
    {
        return;
    }
    if (bShow)
    {
        m_pToolbar->show();
#if 1
        QRect parentRect = geometry();
        //QPoint point = mapToGlobal(QPoint(parentRect.x(), parentRect.height() - m_pToolbar->height()));
        QPoint point = QPoint(parentRect.x(), parentRect.y() + parentRect.height() - m_pToolbar->height());
        QRect toolBarRect = QRect(point, QSize(m_pToolbar->width(), m_pToolbar->height()));
        m_pToolbar->setGeometry(toolBarRect);
#endif
    }
    else
    {
        m_pToolbar->hide();
    }
}

void AutoHideMenuBarDemo::showEvent(QShowEvent* event)
{
    grabMouse();
}
void AutoHideMenuBarDemo::hideEvent(QHideEvent* event)
{
    releaseMouse();
}
