#include <QApplication>
#include <QMainWindow>

#include "bubble.h"
#include "cef/cef.h"
#include "cef/cef_widget.h"
#include "util.h"

int main(int argc, char* argv[]) {
  // We have to set the library path to the exe dir, but we can't use something
  //  like QCoreApplication::applicationDirPath because it requires that we
  //  have an application created already which we don't (and don't want to
  //  because this code is also run for each child process)
  auto exe_path = doogie::Util::ExePath();
  if (exe_path.isNull()) {
    qCritical() << "Unable to get exe path";
    return 2;
  }
  //QCoreApplication::setLibraryPaths({ QFileInfo(exe_path).dir().path() });

  doogie::Cef cef(argc, argv);
  if (cef.EarlyExitCode() >= 0) return cef.EarlyExitCode();

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("cretz");
  QCoreApplication::setApplicationName("Doogie");

  doogie::CefWidget* pWebView = new doogie::CefWidget(cef, doogie::Bubble::DefaultBubble(), QString("file:///home/page/temp/echarts_demo/stacked-bar3d.html"), nullptr, QSize(400, 400));
  pWebView->setMinimumSize(400, 400);
  //pWebView->ViewWidget()->setFixedSize(400, 400);
  pWebView->ViewWidget()->setMinimumSize(400, 400);
  pWebView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  pWebView->adjustSize();
  pWebView->show();
  pWebView->activateWindow();
  pWebView->raise();

  QObject::connect(pWebView, &doogie::CefWidget::LoadStateChanged, [pWebView](){
      pWebView->ExecJs(R"(mul(3, 5))");
  });

  QTimer* pTimer = new QTimer;
  QObject::connect(pTimer, &QTimer::timeout, [](){
      CefDoMessageLoopWork();
  });
  pTimer->start(10);

  return app.exec();
}
