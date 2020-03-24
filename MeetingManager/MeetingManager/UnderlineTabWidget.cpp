#include "UnderlineTabWidget.h"
#include "UnderlineTabBar.h"

UnderlineTabWidget::UnderlineTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
    setTabBar(new UnderlineTabBar);

	QString styleSheet = "QTabWidget:pane{"
                         "       border: 1px solid none; "
                         "       border-top-color: #eaeaea;"
                         "}";
    setStyleSheet(styleSheet);
}

UnderlineTabWidget::~UnderlineTabWidget()
{
}
