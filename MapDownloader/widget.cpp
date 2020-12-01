#pragma execution_character_set("utf-8")
#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog> 
#include "DownloadManager.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_pDownloader(nullptr)
    , m_bStop(false)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_QuitOnClose);

    ui->edtSavePath->setText(QCoreApplication::applicationDirPath());
    
    connect(ui->btnSelectPath, &QPushButton::clicked, this, [this](bool) {
        QString dir = QFileDialog::getExistingDirectory(this, QObject::tr("请选择文件保存路径"), QCoreApplication::applicationDirPath(),
            QFileDialog::ShowDirsOnly
            | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty()) {
            ui->edtSavePath->setText(dir);
        }
    });

    connect(ui->btnDownload, &QPushButton::clicked, this, &Widget::slot_StartDownload);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_StartDownload(bool)
{
    QString strProxyUrl = ui->edtUrl->text();
    QString strPort = ui->edtPort->text();
    QString strUserName = ui->edtName->text();
    QString strPassword = ui->edtPassword->text();
    QString strStartRow = ui->edtStart->text();
    QString strEndRow = ui->edtEnd->text();
    QString strSavePath = ui->edtSavePath->text();

    if(m_pDownloader == nullptr) {
        m_pDownloader = new DownloadManager(this);
    }

    m_pDownloader->setProxy(strProxyUrl, strPort, strUserName, strPassword);
    m_pDownloader->setDownloadRange(strStartRow.toInt(), strEndRow.toInt());
    m_pDownloader->setDownloadPath(strSavePath);
    connect(m_pDownloader, &DownloadManager::signal_DownloadingFile, this, &Widget::slot_DownloadFileStatus);
    connect(m_pDownloader, &DownloadManager::signal_DownloadStatus, this, [this](const QString status) {
        ui->lblDownloadStatus->setText(status);
    });
    m_pDownloader->execute();
}

void Widget::closeEvent(QCloseEvent* event)
{
    m_bStop = true;
    if (m_pDownloader != nullptr) {
        m_pDownloader->stop();
    }
    QWidget::closeEvent(event);
}

void Widget::slot_DownloadFileStatus(const QString file)
{
    ui->lblDownloadStatus->setText(QString("downloading file: %1 ...").arg(file));

}