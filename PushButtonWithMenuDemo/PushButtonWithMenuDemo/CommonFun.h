#pragma once

#include <QFont>
#include <QObject>
#include <QPixmap>
#include <QString>

class CommonFun : public QObject
{
    Q_OBJECT

public:
    CommonFun(QObject* parent);
    ~CommonFun();

    static QFont   getIconFont();
    static QPixmap getRoundedImage(const QString& strImageName, int nRoundWidth);
};
