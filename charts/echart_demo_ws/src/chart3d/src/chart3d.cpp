#include "chart3d.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "bubble.h"
#include "cef/cef.h"
#include "cef/cef_widget.h"
#include "util.h"

namespace chart3d_space {

chart3d::chart3d(QWidget* parent)
	: rviz::Panel(parent)
{
	qDebug() <<  QCoreApplication::arguments();
	int argc = 1;
	char* argv[2];
	char name[128] = {0};
	strcpy(name, QCoreApplication::arguments().at(0).toStdString().c_str());
	argv[0] = name;
	doogie::Cef cef(argc, argv);
#if 0
	if (cef.EarlyExitCode() >= 0) {
		qDebug() <<  "exit";
		return;
	}
#endif

	doogie::CefWidget* pWebView = new doogie::CefWidget(cef, doogie::Bubble::DefaultBubble(), QString("file:///home/page/temp/echarts_demo/stacked-bar3d.html"), nullptr, QSize(400, 400));
	//pWebView->setFixedSize(400, 400);
	//pWebView->ViewWidget()->setFixedSize(400, 400);
	pWebView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pWebView->ViewWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	pWebView->adjustSize();

  	QObject::connect(pWebView, &doogie::CefWidget::LoadStateChanged, [pWebView](){
		pWebView->ExecJs(R"(mul(3, 5))");
	});

	QTimer* pTimer = new QTimer;
	QObject::connect(pTimer, &QTimer::timeout, [](){
			CefDoMessageLoopWork();
			});
	pTimer->start(10);

	QVBoxLayout *mainlayout=new QVBoxLayout;
	mainlayout->addWidget(pWebView);

	setLayout(mainlayout);
}

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(chart3d_space::chart3d, rviz::Panel)
