#include "CommonFun.h"
#include <QFontDatabase>

CommonFun::CommonFun(QObject *parent)
	: QObject(parent)
{
}

CommonFun::~CommonFun()
{
}
//获取图标字体
QFont CommonFun::getIconFont() {
    static int fontId = QFontDatabase::addApplicationFont("Resources/BaseConfig/suningimiconfont.ttf");
    static QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont(fontName);
    iconFont.setPixelSize(12);
    iconFont.setStyleStrategy(QFont::PreferAntialias);
    return QFont(iconFont);
}
