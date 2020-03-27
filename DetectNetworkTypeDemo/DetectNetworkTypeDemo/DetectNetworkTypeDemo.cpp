#include "DetectNetworkTypeDemo.h"
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <QNetworkInterface>
#include <QNetworkSession>
#include <QTcpSocket>

DetectNetworkTypeDemo::DetectNetworkTypeDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    auto operation = [this](QString type) { ui.label->setText(type); };

    QString ip;
    QTcpSocket *socket = new QTcpSocket(this);
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    connect(socket, qOverload<QAbstractSocket::SocketError>(&QTcpSocket::error), []() {});
    connect(socket, &QTcpSocket::connected, [socket, operation]() {
      // 获取网络配置
      QList<QNetworkConfiguration> activeConfigs;
      {
        QNetworkConfigurationManager mgr;
        activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
      }

      // 根据ip解析网络类型
      QString type;
      {
        QString addr = socket->localAddress().toString();
        socket->close();
        socket->deleteLater();

        for (auto conf : activeConfigs) {
          QNetworkSession session(conf);
          auto entries = session.interface().addressEntries();
          for (auto entry : entries) {
            if (entry.ip().toString() == addr) {
              type = conf.bearerTypeName();
              QString name = conf.name();
              break;
            }
          }
        }
      }

      // 回调
      operation(type);
    });
    socket->connectToHost("www.suning.com", 80);
    //if (socket.waitForConnected(500)) {
    //  qDebug() << "local IPv4 address for Internet connectivity is"
    //           << socket.localAddress();
    //  ip = socket.localAddress().toString();
    //} else {
    //  qWarning() << "could not determine local IPv4 address:"
    //             << socket.errorString();
    //}
}
