#pragma once

#include <QtWidgets/QDialog>
#include "ui_AutoHideMenuBarDemo.h"

class ShareDesktopToolbar;
class AutoHideMenuBarDemo : public QDialog
{
    Q_OBJECT

public:
    AutoHideMenuBarDemo(QWidget *parent = Q_NULLPTR);

    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);

private:
    bool isMouseInRect(QMouseEvent* event);
    void startTimer(bool bStart);
    void ShowToolbar(bool bShow);

private:
    Ui::AutoHideMenuBarDemoClass ui;
    ShareDesktopToolbar* m_pToolbar;
    QTimer*  m_pShowToolbarTimer;
};
