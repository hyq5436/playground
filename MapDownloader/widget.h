#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class DownloadManager;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void closeEvent(QCloseEvent* event);
public slots:
    void slot_StartDownload(bool);
    void slot_DownloadFileStatus(const QString file);

private:
    Ui::Widget *ui;

    DownloadManager* m_pDownloader;
    bool m_bStop;
};
#endif // WIDGET_H
