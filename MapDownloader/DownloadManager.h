#pragma once

#include <QObject>
#include <QtNetwork>

class QSslError;

class DownloadManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QVector<QNetworkReply*> currentDownloads;
    QMap<QNetworkReply*, QString> currentDownloadTasks;

public:
    DownloadManager(QObject* parent = nullptr);

    void setProxy(const QString& url, const QString& port, const QString& user, const QString& password);
    void setDownloadRange(int iStart, int iEnd);
    void setDownloadPath(const QString& path);
    void stop();

    void doDownload(const QUrl& url, const QString& fileName);
    static QString saveFileName(const QUrl& url);
    bool saveToDisk(const QString& filename, QIODevice* data);
    static bool isHttpRedirect(QNetworkReply* reply);

signals:
    void signal_DownloadingFile(const QString file);
    void signal_DownloadStatus(const QString status);

public slots:
    void execute();
    void downloadFinished(QNetworkReply* reply);
    void sslErrors(const QList<QSslError>& errors);

private:
    QString m_strUrl;
    QString m_strPort;
    QString m_strUser;
    QString m_strPassword;

    int m_iStartRow;
    int m_iEndRow;

    QString m_strSavePath;

    bool m_bStop;
};
