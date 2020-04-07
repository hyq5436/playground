#pragma execution_character_set("utf-8")
#include "CommonFun.h"
#include <QBitmap>
#include <QFontDatabase>
#include <QPainter>

CommonFun::CommonFun(QObject* parent) : QObject(parent) {}

CommonFun::~CommonFun() {}
//获取图标字体
QFont CommonFun::getIconFont()
{
    static int     fontId   = QFontDatabase::addApplicationFont("Resources/BaseConfig/suningimiconfont.ttf");
    static QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont          iconFont(fontName);
    iconFont.setPixelSize(12);
    iconFont.setStyleStrategy(QFont::PreferAntialias);
    return QFont(iconFont);
}

//获取圆形图片
QPixmap CommonFun::getRoundedImage(const QString& strImageName, int nRoundWidth)
{
    QBitmap maskBitmap(2 * nRoundWidth, 2 * nRoundWidth); //放大为圆形2倍以消锯齿
    maskBitmap.fill(Qt::white);
    QPainter painter(&maskBitmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black); //原本是blue，mac下面是黑色才会成功生成蒙板图片
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawEllipse(0, 0, maskBitmap.width(), maskBitmap.height()); //绘制圆形

    int padding = 10;
    QRect pieRect = QRect(2 * (nRoundWidth * 2 / 3 - padding),
              2 * (nRoundWidth * 2 / 3 - padding),
              2 * (nRoundWidth / 3 + 2 * padding), 2 * (nRoundWidth / 3 + 2 * padding));
    painter.setBrush(Qt::white); //原本是blue，mac下面是黑色才会成功生成蒙板图片
    painter.drawEllipse(pieRect);

    QPixmap imagePixmap(strImageName);
    imagePixmap = imagePixmap.scaled(maskBitmap.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imagePixmap.setMask(maskBitmap); //设置蒙板(显示圆角图片)

    imagePixmap = imagePixmap.scaled(nRoundWidth, nRoundWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return imagePixmap;
}
