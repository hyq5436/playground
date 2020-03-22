#pragma once

#include <QTabWidget>

class UnderlineTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	UnderlineTabWidget(QWidget *parent = Q_NULLPTR);
	~UnderlineTabWidget();
};
