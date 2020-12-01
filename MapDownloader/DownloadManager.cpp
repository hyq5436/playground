#include "DownloadManager.h"
#include <QDebug>
#include <QMessageBox>

using namespace std;

namespace {
    const int MAX_DOWNLOAD_TASKS = 50;
    const int TASK_CHECK_DELAY = 200;
}
DownloadManager::DownloadManager(QObject *parent)
    : QObject(parent)
    , m_iStartRow(0)
    , m_iEndRow(0)
    , m_bStop(false)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
        SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::doDownload(const QUrl& url, const QString& fileName)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = manager.get(request);

#if QT_CONFIG(ssl)
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
        SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
    currentDownloadTasks[reply] = fileName;

}

QString DownloadManager::saveFileName(const QUrl& url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

bool DownloadManager::saveToDisk(const QString& filename, QIODevice* data)
{
    QDir dir;
    QFileInfo fi(filename);
    QString path = fi.dir().absolutePath();
    dir.mkpath(path);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        emit signal_DownloadStatus(QString("Could not open %1 for writing: %2").arg(filename).arg(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

bool DownloadManager::isHttpRedirect(QNetworkReply* reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
        || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void DownloadManager::execute()
{
    // 10 start
    // https://mape.shanghai-map.net/arcgis/rest/services/SHMAP_D/MapServer/tile/10/169096/876143
    // https://mape.shanghai-map.net/arcgis/rest/services/SHMAP_D/MapServer/tile/10/173173/880450

    int iLevel = 9;
    QString strUrl("https://mape.shanghai-map.net/arcgis/rest/services/SHMAP_D/MapServer/tile/%1/%2/%3");
    QString name;

    // get one task
    iLevel = 10;
    for (size_t i = m_iStartRow; i <= m_iEndRow; i++)
    {
        for (size_t j = 876143; j <= 880450; j++)
        {
            if (m_bStop)
            {
                QCoreApplication::instance()->quit();
                return;
            }
            while (currentDownloads.length() >= MAX_DOWNLOAD_TASKS)
            {
                if (m_bStop)
                {
                    QCoreApplication::instance()->quit();
                    return;
                }
                QCoreApplication::processEvents();
            }

            QString temp = strUrl.arg(iLevel).arg(i).arg(j);
            QUrl url(temp);

            name = QString("%1/%2/%3/%4.png").arg(m_strSavePath).arg(iLevel).arg(i).arg(j);
            emit signal_DownloadingFile(name);
            doDownload(url, name);
        }
    }

}

void DownloadManager::sslErrors(const QList<QSslError>& sslErrors)
{
#if QT_CONFIG(ssl)
    for (const QSslError& error : sslErrors)
        emit signal_DownloadStatus(QString("SSL error: %1").arg(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply* reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        emit signal_DownloadStatus(QString("Download of %1 failed: %2").arg(url.toEncoded().constData()).arg(reply->errorString()));
    }
    else {
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        }
        else {
            QString filename = currentDownloadTasks[reply];
            if (saveToDisk(filename, reply)) {
                //qDebug() << QString("Download of %1 succeeded (saved to %2)").arg(url.toEncoded().constData()).arg(filename);
            }
        }
    }

    currentDownloadTasks.remove(reply);
    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
        // all downloads finished
        emit signal_DownloadStatus("Download finished.");
        QMessageBox msgBox;
        msgBox.setText("Dowload finished.");
        msgBox.exec();

        QCoreApplication::instance()->quit();
    }
}

void DownloadManager::setProxy(const QString& url, const QString& port, const QString& user, const QString& password)
{
    if(url.isEmpty())
        return;

    m_strUrl = url;
    m_strPort = port;
    m_strUser = user;
    m_strPassword = password;

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(m_strUrl);
    proxy.setPort(m_strPort.toUShort());
    proxy.setUser(m_strUser);
    proxy.setPassword(m_strPassword);

    manager.setProxy(proxy);
}

void DownloadManager::setDownloadRange(int iStart, int iEnd)
{
    if (iStart == 0) {
        m_iStartRow = 169096;
    }
    else {
        m_iStartRow = iStart;
    }
    
    if (iEnd == 0) {
        m_iEndRow = 173173;
    }
    else {
        m_iEndRow = iEnd;
    }

    m_iStartRow = qMax(m_iStartRow, 169096);
    m_iStartRow = qMin(m_iStartRow, 173173);

    m_iEndRow = qMin(m_iEndRow, 173173);
    m_iEndRow = qMax(m_iStartRow, m_iEndRow);
}

void DownloadManager::setDownloadPath(const QString& path)
{
    m_strSavePath = path;
}

void DownloadManager::stop()
{
    m_bStop = true;
}
