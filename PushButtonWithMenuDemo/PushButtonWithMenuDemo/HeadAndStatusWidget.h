#pragma once

#include <QWidget>

class HeadAndStatusWidget : public QWidget
{
    Q_OBJECT

public:
    HeadAndStatusWidget(QWidget *parent);
    ~HeadAndStatusWidget();

    void paintEvent(QPaintEvent* event) override;
};
