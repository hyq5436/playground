#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!QFile::exists("app_zh_CN.qm"))
        qWarning("failed-no file");

#if 0
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("myapp_" + QLocale::system().name());
    a.installTranslator(&myappTranslator);
#endif


    QTranslator enTranslator;
    if (enTranslator.load("app_en_GB"))
        a.installTranslator(&enTranslator);


    QTranslator translator;
    if (translator.load("app_zh_CN"))
        a.installTranslator(&translator);


    qDebug() << QLocale().uiLanguages();
    qDebug() << QLocale().bcp47Name();
    Widget w;
    w.show();
    return a.exec();
}
