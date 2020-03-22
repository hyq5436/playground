#pragma once

#include <QTabBar>

class QPaintEvent;

class UnderlineTabBar : public QTabBar
{
	Q_OBJECT

public:
	UnderlineTabBar(QWidget *parent = Q_NULLPTR);
	~UnderlineTabBar();

	void paintEvent(QPaintEvent* event) override;
    QSize tabSizeHint(int index) const override;
};
