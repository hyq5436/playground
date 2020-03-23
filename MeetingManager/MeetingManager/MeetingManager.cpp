#pragma execution_character_set("utf-8")

#include "MeetingManager.h"
#include <QDebug>
#include <QIcon>
#include <QItemDelegate>
#include <QListWidgetItem>
#include <QPainter>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>

namespace {
static const int MeetingIconRole = Qt::UserRole + 1;
}
class MeetingNavDelegate : public QItemDelegate {
public:
    MeetingNavDelegate(QObject* parent) : QItemDelegate(parent){};
    void paint(QPainter* painter,
               const QStyleOptionViewItem& option,
               const QModelIndex& index) const override {
        if (option.state & QStyle::State_Selected) {
            QBrush brush(QColor("#c7e2fb"));
            QRect fill_rect(option.rect.x(), option.rect.y(),
                            option.rect.width(), option.rect.height());
            painter->fillRect(fill_rect, brush);
        } else if (option.state & QStyle::State_MouseOver) {
            QBrush brush(QColor("#e2effc"));
            QRect fill_rect(option.rect.x(), option.rect.y(),
                            option.rect.width(), option.rect.height());
            painter->fillRect(fill_rect, brush);
        }

        QString title = index.data(Qt::DisplayRole).toString();
        QString iconPath = index.data(MeetingIconRole).toString();

        //头像显示区域
        QRect iconRect =
            QRect(option.rect.x() + 20, option.rect.y() + 10, 30, 30);
        QPixmap icon(iconPath);
        painter->drawPixmap(iconRect, icon);

        //
        QRect titleRect =
            QRect(option.rect.x() + 30 + 30, option.rect.y(), 100, 50);
        painter->drawText(titleRect, title, QTextOption(Qt::AlignVCenter));
    }

    QSize sizeHint(const QStyleOptionViewItem& option,
                   const QModelIndex& index) const override {
        return QSize(100, 50);
    }
};

MeetingManager::MeetingManager(QWidget* parent) : QWidget(parent) {
    ui.setupUi(this);
    addMeetingType();
}

void MeetingManager::addMeetingType() {
    auto* model = new QStandardItemModel(this);
    auto* delegate = new MeetingNavDelegate(this);
    ui.listMeetingNav->setModel(model);
    ui.listMeetingNav->setItemDelegate(delegate);

    auto* allHistory =
        new QStandardItem(QIcon("Resources/history.png"), tr("我的会议"));
    allHistory->setData(QString("Resources/history.png"), MeetingIconRole);

    auto* voice =
        new QStandardItem(QIcon("Resources/voice.png"), tr("语音会议"));
    voice->setData(QString("Resources/voice.png"), MeetingIconRole);

    auto* video =
        new QStandardItem(QIcon("Resources/video.png"), tr("视频会议"));
    video->setData(QString("Resources/video.png"), MeetingIconRole);

    auto* live = new QStandardItem(QIcon("Resources/live.png"), tr("直播"));
    live->setData(QString("Resources/live.png"), MeetingIconRole);

    model->appendRow(allHistory);
    model->appendRow(voice);
    model->appendRow(video);
    model->appendRow(live);

	auto* pButtonContainer = new QWidget(ui.tabWidget);
    pButtonContainer->resize(QSize(100, ui.tabWidget->tabBar()->height()));
    auto* pLayout = new QHBoxLayout;
    pButtonContainer->setLayout(pLayout);
	
    auto* pButton = new QPushButton(ui.tabWidget);
    pLayout->addWidget(pButton);
    ui.tabWidget->setCornerWidget(pButtonContainer);
}
