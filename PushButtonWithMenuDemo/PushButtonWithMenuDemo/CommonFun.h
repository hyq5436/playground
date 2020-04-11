#pragma execution_character_set("utf-8")
#pragma once

#include <QFont>
#include <QObject>
#include <QPixmap>
#include <QString>

class CommonFun : public QObject {
    Q_OBJECT

public:
    CommonFun(QObject* parent);
    ~CommonFun();

    static QFont getIconFont();
    static QPixmap getRoundedImage(const QString& strImageName,
                                   int nRoundWidth);
    static QPixmap getRoundedCornerImage(const QString& strImageName, int nRoundWidth);
    static QPixmap getIconFontPixmap(const QString& strIcon,
                                     const QColor& color = QColor("#FFFFFF"),
                                     const QSize& size = QSize(30, 30),
                                     int fontsize = 16);  // iconfontת转成pixmap
};
