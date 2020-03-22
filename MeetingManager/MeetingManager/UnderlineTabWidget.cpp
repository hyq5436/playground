#include "UnderlineTabWidget.h"
#include "UnderlineTabBar.h"

UnderlineTabWidget::UnderlineTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
    setTabBar(new UnderlineTabBar);
}

UnderlineTabWidget::~UnderlineTabWidget()
{
}
