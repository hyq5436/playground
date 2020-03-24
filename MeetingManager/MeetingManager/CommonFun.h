#pragma once

#include <QObject>
#include <QFont>

class CommonFun : public QObject
{
	Q_OBJECT

public:
	CommonFun(QObject *parent);
	~CommonFun();

    QFont getIconFont();
};
