#ifndef INTERNATIONALUTIL_H
#define INTERNATIONALUTIL_H

#include <QObject>

class InternationalUtil : public QObject
{
    Q_OBJECT
public:
    explicit InternationalUtil(QObject *parent = nullptr);


    void loadTranslateFile(const QString& local);
signals:

};

#endif // INTERNATIONALUTIL_H
