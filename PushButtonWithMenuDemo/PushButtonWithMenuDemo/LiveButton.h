#pragma once

#include <QPushButton>

class QMouseEvent;
class QPaintEvent;
class LiveButton : public QPushButton
{
    Q_OBJECT

public:
    LiveButton(QWidget *parent);
    ~LiveButton();

    bool event(QEvent* e) override;
    void paintEvent(QPaintEvent* event) override;

private:
    bool handleMouseMoveEvent(QMouseEvent* e);
};
