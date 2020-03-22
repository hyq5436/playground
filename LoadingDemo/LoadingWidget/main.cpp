#include "LoadingWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingWidget* m_pLoadingWindow = new LoadingWidget();
    m_pLoadingWindow->setLoadingText("loading...");
    m_pLoadingWindow->showWindow();
    return a.exec();
}
